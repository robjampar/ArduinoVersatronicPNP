#include <math.h> 
#include "Stepper.h"
#include "ArmBoard.h"
#include "Controller.h"
#include "FrontLCD.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <TimedAction.h>
#include <TimerOne.h>

Stepper *stepperX; // z
Stepper *stepperY; // arm 0
Stepper *stepperZ; // arm 1
Stepper *stepperC; // rotate

ArmBoard *armBoard;
Controller *controller;
FrontLCD *frontLCD;

void updateLCD(){
  frontLCD->update();
}

TimedAction lcdThread = TimedAction(100, updateLCD);


void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  stepperX = new Stepper(39, 41, 43, 45, 5000);
  stepperY = new Stepper(47, 49, 51, 53, 5000);
  stepperZ = new Stepper(38, 40, 42, 44, 5000);
  stepperC = new Stepper(46, 48, 50, 52, 5000);
  
  armBoard = new ArmBoard(&Serial1);
  controller = new Controller(&Serial);
  //frontLCD = new FrontLCD(armBoard);

  stepperC->rotate(360*10);


  Timer1.initialize(50);         // initialize timer1, and set a 50us period
  Timer1.attachInterrupt(callback); 
}


void callback() { // Time sensitive loop
  stepperC->update();
  //stepperX->update();
}

void loop() { // Non-time sensitive loop
  
  controller->update();
  armBoard->update();
  lcdThread.check();

//  if (armBoard->limitState[3] < 250) {
//    stepperC->direction(!stepperC->currentDirection);
//  }

}

/** Menu 
 *  
 */
void menu() {
  
}



void home() {

  /**
   * Move fast check switch, move slow check switch
   */
}

void pick() {

}

void place() {
  
}

const double armLengthA = 17.5;
const double armLengthB = 17.6;

/**
 * Converts cartesian co-ordinates to SCARA
 */
void moveTo(double x, double y, double speed) {

  double a = armLengthA;
  double b = armLengthB;
  double c = sqrt(pow(x, 2.0) + pow(y, 2.0)); // c = (x^2 + y^2)^0.5

  double angleB = acos(((pow(a, 2.0) + pow(c, 2.0) - pow(b, 2.0)) / (2.0 * a * c))); // b = cos^-1(a^2 + c^2 - b^2 / 2ac)
  double angleC = acos(((pow(a, 2.0) + pow(b, 2.0) - pow(c, 2.0)) / (2.0 * a * b))); // c = cos^-1(a^2 + b^2 - c^2 / 2ab)
  double angleD = atan(y/x);
  double angleE = 90.0 + acos(y / a);
  
  
  double angleArmA = angleB + angleD;
  double angleArmB = angleC - angleE;
  
  moveToAngle(angleArmA, angleArmB, speed);
}


/**
 * 
 */
void moveToAngle(double aX, double aY, double speed) {

}
