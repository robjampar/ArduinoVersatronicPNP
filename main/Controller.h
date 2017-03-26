#ifndef CONTROLLER_H
#define CONTROLLER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Controller {

  private:

    const int heartbeatUpdateRate = 5000;

    String serialCommand = "";

    unsigned long heartbeatUpdateTime = 0;  
        
    HardwareSerial *serialPort;

  public:
        
    Controller(HardwareSerial *serialPort);

    void update();
    void heartbeat();
    void processCommand(String command);
};

#endif
