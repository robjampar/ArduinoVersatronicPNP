#ifndef FRONT_LCD_H
#define FRONT_LCD_H

#include "ArmBoard.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const int lcdUpdateRate = 50; // lcd update rate in ms

class FrontLCD {

  private:
  
    int lcdUpateTime = 0;
    ArmBoard *armBoard;
   
  public:
        
    FrontLCD(ArmBoard *armBoard);

    void update();
};

#endif
