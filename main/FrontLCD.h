#ifndef FRONT_LCD_H
#define FRONT_LCD_H

#include "ArmBoard.h"


#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


class FrontLCD {

  private:
  
    ArmBoard *armBoard;
    
  public:
        
    FrontLCD(ArmBoard *armBoard);

    void update();
};

#endif
