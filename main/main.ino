#include <math.h> 

const byte armBoardLimitStateCommands[4] = {1, 2, 3, 4};
const byte armBoardRelayCommands[4] = {27, 28, 29, 30};
const int limitStateUpdateRate = 20; // Limit state update rate in ms
const double armLengthA = 17.5;
const double armLengthB = 17.6;

int timeSinceLimitStateUpate = 0;
byte awaitingLimitStateResponseIndex = 0;
byte limitState[4] = {0};
bool relayState = {false};

void setup() {
  Serial.begin(9600);   // Control PC Serial (From USB)
  Serial1.begin(9600);  // Arm Board RS232

  Serial1.write(armBoardRelayCommands[1]); // Disable Vacuum
  Serial1.write(armBoardRelayCommands[3]); // Disable Vacuum Valve
}

void loop() {
  updateLimitState();
}

/**
 * Command from Computer.
 */
void serialEvent1() {
 
}

/**
 * Response from Arm Board.
 */
void serialEvent1() {
  while (Serial1.available()) {
    limitState[awaitingLimitStateResponseIndex] = Serial1.read();
    awaitingLimitStateResponseIndex = awaitingLimitStateResponseIndex++ % 4;
  }
}

void updateLimitStates() {
  if (timeSinceLimitStateUpate > limitStateUpdateRate) {
    for (int i = 0; i < 4; i++) {
      Serial1.write(armBoardLimitStateCommands[i]);
    }
  }
}

void home() {
  
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

  double angleB = acos(((pow(a, 2.0) + pow(c, 2.0) - pow(b, 2.0)) / (2.0 * a * c))) // b = cos^-1(a^2 + c^2 - b^2 / 2ac)
  double angleC = acos(((pow(a, 2.0) + pow(b, 2.0) - pow(c, 2.0)) / (2.0 * a * b))) // c = cos^-1(a^2 + b^2 - c^2 / 2ab)
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
