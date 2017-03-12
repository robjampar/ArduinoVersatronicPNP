#include <math.h> 
#include "Stepper.h"
#include "ArmBoard.h"
#include "FrontLCD.h"

const int heartbeatUpdateRate = 1000; // lcd update rate in ms

String serialCommand = "";

int heartbeatUpdateTime = 0;


Stepper *stepperC;
ArmBoard *armBoard;
FrontLCD *frontLCD;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  stepperC = new Stepper(46, 48, 50, 52, 500);
  armBoard = new ArmBoard(&Serial1);
  frontLCD = new FrontLCD(armBoard);
  

  serialCommand.reserve(128);
  Serial.begin(9600);   // Control Commands from PC Serial (via USB)

  stepperC->step(100000);

  Serial.write("Versatronics PNP setup complete...\n");
}


void loop() {
  heartbeat();
  updateSerials();

  armBoard->update();
  stepperC->update();
  frontLCD->update();

  if (armBoard->limitState[3] < 220) {
    stepperC->direction(!stepperC->currentDirection);
  }
}

/** Menu 
 *  
 */
void menu() {
  
}


void heartbeat() {
  int currentTime = millis();
  int timeSinceHeartbeatUpateTime = currentTime - heartbeatUpdateTime;
  if (timeSinceHeartbeatUpateTime > heartbeatUpdateRate) {
    heartbeatUpdateTime = currentTime;

    char heartbeat_message [128];
    
    sprintf (heartbeat_message, "---------- Versatronics PNP heartbeat ----------\nlimit_state: %d %d %d %d\nstep_state: %lu\n", 
    armBoard->limitState[0], 
    armBoard->limitState[1], 
    armBoard->limitState[2], 
    armBoard->limitState[3], 
    stepperC->stepsRemaining);
    
    Serial.write(heartbeat_message);
  }
}

void updateSerials() {
  /**
  * Command from Computer (G-code)
  */
  while (Serial.available()) {
    char commandChar = (char)Serial.read();
    serialCommand += commandChar;
    if (commandChar == '\n') {
      char received_command_message [128];
    
      sprintf (received_command_message, "Received command: %s", serialCommand.c_str());
      Serial.write(received_command_message);
      
      processSerialCommand(serialCommand);
      serialCommand = "";
    }
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
