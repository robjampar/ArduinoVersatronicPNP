#ifndef STEPPER_H
#define STEPPER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define CLOCKWISE true
#define COUNTERCLOCKWISE false

//Stepper stepperX = Stepper(1, 2, 3, 4, 500);
//Stepper stepperY = Stepper(1, 2, 3, 4, 500);
//Stepper stepperZ = Stepper(1, 2, 3, 4, 500);

//52,50,48,46 = C

// mode, enable, dir, step 
// X = (green/red, black/white, grey/black, purple)
// Y = (yellow/black, purple/red, pink, orange)
// Z = (grey, pink/black, grey/blue, yellow)
// C = (grey, red/white, red/green, brown)

// port no / port specs / motor / arduino pins (mode, enable, dir, step) 
// 1 = D1 - 2, 4, 6, 8 = C = 52, 50, 48, 46 (ena = 44)
// 2 = D1 - 1, 3, 5, 7 = X = 53, 51, 49, 47 (ena = 44)
// 3 = D2 - 2, 4, 6, 8 = Y = 42, 40, 38, 36 (ena = 34)
// 4 = D2 - 1, 3, 5, 7 = Z = 43, 41, 39, 37 (ena = 34)

class Stepper {

  private:
    int dirPin;
    int stepPin;
    int enablePin;
    int modePin;
    
    float currentAngle = 0;
    float currentVelocity = 0;
    float maxVelocity = 1;

    float stepsPerRevolution;

    unsigned long nextStepTime = 0;
    void step();

  public:

    unsigned long stepsRemaining = 0;
    bool currentDirection;
    
    Stepper(int modePin,
            int enablePin,
            int dirPin,
            int stepPin,
            float stepsPerRevolution,
            float maxVelocity = 1,
            bool direction = CLOCKWISE);

    void direction(bool direction);
    void step(long steps);
    void enable(bool enable = true);
    void mode(int mode = 1);
    void rotate(float degrees);

    void update();
};

#endif
