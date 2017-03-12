#include "Stepper.h"

Stepper::Stepper(int modePin, int enablePin, int dirPin, int stepPin, float stepsPerRevolution, float maxVelocity, bool direction) {

  this->dirPin = dirPin;
  this->stepPin = stepPin;
  this->enablePin = enablePin;
  this->modePin = modePin;
  this->currentDirection = direction;
  this->stepsPerRevolution = stepsPerRevolution;
  this->currentVelocity = 0;
  this->maxVelocity = maxVelocity;
  
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(modePin, OUTPUT);

  digitalWrite(this->dirPin, (this->currentDirection == CLOCKWISE?HIGH:LOW));
  this->enable(true);
  
}

void Stepper::step() {
  if (this->stepsRemaining > 0) {
    digitalWrite(this->stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->stepPin, LOW);

    this->stepsRemaining = this->stepsRemaining - 1;
  }
}

void Stepper::step(long steps) {
  this->stepsRemaining += steps;
}

void Stepper::direction(bool direction) {
  this->currentDirection = direction;
  digitalWrite(this->dirPin, (this->currentDirection == CLOCKWISE?HIGH:LOW));
}

void Stepper::enable(bool enable) {
  digitalWrite(this->enablePin, (enable?HIGH:LOW));
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

void Stepper::update() {
  if (this->stepsRemaining > 0) {
    unsigned long currentTime = micros();
    if (this->nextStepTime < currentTime){
      this->step();
      this->nextStepTime = currentTime + 200;
    }
  }

}
