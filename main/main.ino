#include <math.h> 
#include "Stepper.h"
#define ENABLE_LCD true

#if ENABLE_LCD 
  #include <Wire.h>
  #include <LiquidCrystal_PCF8574.h>
  LiquidCrystal_PCF8574 lcd(0x27);
#endif

const byte armCommands[8] = {1, 2, 3, 4, 27, 28, 29, 30};
const int armStateUpdateRate = 1000; // state update rate in ms
const double armLengthA = 17.5;
const double armLengthB = 17.6;

String serialCommand = "";

int armStateUpateTime = 0;
int limitStateResponseIndex = 0;
bool pendingResponse = false;
int limitState[4] = {0};

//Stepper stepperX = Stepper(1, 2, 3, 4, 500);
//Stepper stepperY = Stepper(1, 2, 3, 4, 500);
//Stepper stepperZ = Stepper(1, 2, 3, 4, 500);
//Stepper stepperC = Stepper(1, 2, 3, 4, 500);

void setup() {

  serialCommand.reserve(128);

#if ENABLE_LCD 
  lcd.begin(16,2);
  lcd.setBacklight(255);
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
#endif
  
  SerialUSB.begin(9600);   // Control Commands from PC Serial (via USB)
  Serial1.begin(9600);  // Arm Board (via RS232)

  Serial1.write(armCommands[5]); // Disable Vacuum
  Serial1.write(armCommands[7]); // Disable Vacuum Valve

  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  updateSerials();
  updateLimitStates();
  updateLcd();
}

/** Menu 
 *  
 */
void menu() {
  
}

void updateSerials() {
  /**
  * Command from Computer (G-code)
  */
  while (SerialUSB.available()) {
    char commandChar = (char)SerialUSB.read();
    SerialUSB.write(commandChar);
    serialCommand += commandChar;
    if (commandChar == '\n') {
      processSerialCommand(serialCommand);
      serialCommand = "";
    }
  }
  
  /**
   * Response from Arm Board.
   */
  while (Serial1.available()) {
    int response = (int)Serial1.read();
    char line_1[64];
    sprintf (line_1, "Arm response for index %x: '%x'\n", limitStateResponseIndex, response);
    SerialUSB.write(line_1);
    processArmResponse(response);
  }
}

void processSerialCommand(String command) {
  
  /*
   * G0 X{0} Y{0} Z{0} F{0} move
   * G28 X Y Z home
   * 
   * M800 ID{Id} I{Index} feeder 
   * M801 M802 solenoid on/off
   * M803 M804 pump on/off
   */
   
}

void processArmResponse(int response) {
    pendingResponse = false;
    limitState[limitStateResponseIndex] = response;
}

bool swapper = true;

void updateLimitStates() {
  int currentTime = millis();
  int timeSinceArmStateUpateTime = currentTime - armStateUpateTime;
  if (timeSinceArmStateUpateTime > armStateUpdateRate) {
    armStateUpateTime = currentTime;
    SerialUSB.write("Updating Limit state\n"); 
    limitStateResponseIndex = (limitStateResponseIndex + 1) % 4;
    Serial1.write(armCommands[limitStateResponseIndex]);
  }
}

void updateLcd() {
  char line_1 [16];
  sprintf (line_1, "%d %d %d %d       ", limitState[0], limitState[1], limitState[2], limitState[3]);
  lcd.setCursor(0,0);
  lcd.print(line_1);
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
