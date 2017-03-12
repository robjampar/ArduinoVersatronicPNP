#include "ArmBoard.h"

ArmBoard::ArmBoard(HardwareSerial *serialPort) {

  this->serialPort = serialPort;
  this->serialPort->begin(9600);
  
  this->serialPort->write(armCommands[5]); // Disable Vacuum
  this->serialPort->write(armCommands[7]); // Disable Vacuum Valve
  
}

void ArmBoard::update() {

  // Send serial commands
  int currentTime = millis();
  int timeSinceArmStateUpateTime = currentTime - armStateUpateTime;
  if (timeSinceArmStateUpateTime > armStateUpdateRate) {
    this->armStateUpateTime = currentTime;
    //Serial.write("Updating Limit state\n"); 
    this->limitStateResponseIndex = (limitStateResponseIndex + 1) % 4;
    this->serialPort->write(armCommands[limitStateResponseIndex]);
  }

  // Recieve serial commands
  while (this->serialPort->available()) {
    int response = (int)this->serialPort->read();
    char line_1[64];
    //sprintf (line_1, "Arm response for index %x: '%x'\n", limitStateResponseIndex, response);
    //Serial.write(line_1);
    this->processArmResponse(response);
  }
}

void ArmBoard::processArmResponse(int response) {
    this->pendingResponse = false;
    this->limitState[limitStateResponseIndex] = response;
}


