#ifndef STEPPER_H
#define STEPPER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define CLOCKWISE true
#define COUNTERCLOCKWISE false

class Stepper {

  private:
    int dirPin;
    int stepPin;
    int enablePin;
    int modePin;
    float currentAngle = 0;
    float zeroOffet = 0;
    bool homed;
    bool direction;
    float stepsPerRevolution;

    int stepsRemaining;
    unsigned long nextStepTime;
    void step();

  public:
    Stepper(int dirPin,
            int stepPin,
            int enablePin,
            int modePin,
            float stepsPerRevolution,
            bool direction = CLOCKWISE);

    void step(int steps);
    void enable(bool enable = true);
    void mode(int mode = 1);
    void rotate(float degrees);

    void run();
};

#endif
