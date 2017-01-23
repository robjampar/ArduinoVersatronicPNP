#include "Stepper.h"

Stepper::Stepper(int dirPin, int stepPin, int enablePin, int modePin, float stepsPerRevolution, bool direction) {

  this->dirPin = dirPin;
  this->stepPin = stepPin;
  this->enablePin = enablePin;
  this->modePin = modePin;
  this->direction = direction;
  this->stepsPerRevolution = stepsPerRevolution;
  
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(modePin, OUTPUT);

  this->enable(true);
  
}

void Stepper::step() {
  if (this->stepsRemaining != 0) {
    digitalWrite(this->stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->stepPin, LOW);

    this->stepsRemaining = this->stepsRemaining - 1;
  }
}

void Stepper::step(int steps) {
  this->stepsRemaining += steps;
}

void Stepper::enable(bool enable) {
  digitalWrite(this->modePin, (enable?LOW:HIGH));
}

void Stepper::mode(int mode) {

  switch (mode) {
    case 1:
    digitalWrite(this->modePin, HIGH);
    break;

    case 2:
    digitalWrite(this->modePin, LOW);
    break;
  }
  
}

void Stepper::rotate(float degrees) {
  step((degrees * this->stepsPerRevolution)/360);
}

void Stepper::run() {
  if (this->stepsRemaining != 0) {
    unsigned long currentTime = micros();
    if (this->nextStepTime <= currentTime){
      step();
      unsigned long currentTime = micros();
      this->nextStepTime = currentTime + 50;
    }
  }

}
