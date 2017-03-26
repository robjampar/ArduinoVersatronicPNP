#include "Controller.h"

Controller::Controller(HardwareSerial *serialPort) {

  this->serialPort = serialPort;
  this->serialPort->begin(115200);

  this->serialPort->write("Versatronics PNP setup complete...\n");
}


void Controller::heartbeat() {
  unsigned long currentTime = millis();
  unsigned long timeSinceHeartbeatUpateTime = currentTime - this->heartbeatUpdateTime;
  if (timeSinceHeartbeatUpateTime > heartbeatUpdateRate) {
    this->heartbeatUpdateTime = currentTime;
    
    this->serialPort->write("-HB-\n");
  }
}


void Controller::update() {
  /**
  * Command from Computer (G-code)
  */

  this->heartbeat();
  while (this->serialPort->available()) {
    char commandChar = (char)this->serialPort->read();
    this->serialCommand = this->serialCommand + commandChar;
    if (commandChar == '\n') {
    
      this->serialPort->write("Received command: ");
      this->serialPort->write(this->serialCommand.c_str());
      
      this->processCommand(this->serialCommand);
      this->serialCommand = "";
    }
  }
}

void Controller::processCommand(String command) {
  
  /*
   * G0 X{0} Y{0} Z{0} F{0} move
   * G28 X Y Z home
   * 
   * M800 ID{Id} I{Index} feeder 
   * M801 M802 solenoid on/off
   * M803 M804 pump on/off
   */
   
}
