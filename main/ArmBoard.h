#ifndef ARMBOARD_H
#define ARMBOARD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const byte armCommands[8] = {1, 2, 3, 4, 27, 28, 29, 30};
const int armStateUpdateRate = 10; // state update rate in ms

class ArmBoard {

  private:
    
    int armStateUpateTime = 0;
    
    int limitStateResponseIndex = 0;
    bool pendingResponse = false;
    
    HardwareSerial *serialPort;

    void processArmResponse(int response);

  public:
    int limitState[4] = {0};
        
    ArmBoard(HardwareSerial *serialPort);

    void update();
};

#endif
