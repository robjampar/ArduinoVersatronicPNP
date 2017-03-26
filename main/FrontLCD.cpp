#include "FrontLCD.h"

#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);

FrontLCD::FrontLCD(ArmBoard *armBoard) {

  this->armBoard = armBoard;
  
  lcd.begin(16,2);
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  
}

void FrontLCD::update() {
  char line_1 [16];
  sprintf (line_1, "%d %d %d %d       ", this->armBoard->limitState[0], this->armBoard->limitState[1], this->armBoard->limitState[2], this->armBoard->limitState[3]);
  lcd.setCursor(0,0);
  lcd.print(line_1);
}

