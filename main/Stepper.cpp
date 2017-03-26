#include "Stepper.h"

Stepper::Stepper(int modePin, int enablePin, int dirPin, int stepPin, float stepsPerRevolution, float maxRPS, float acceleration, bool direction) {

  this->dirPin = dirPin;
  this->stepPin = stepPin;
  this->enablePin = enablePin;
  this->modePin = modePin;
  this->currentDirection = direction;
  this->stepsPerRevolution = stepsPerRevolution;
  this->currentRPS = 0;
  this->maxRPS = maxRPS;
  this->acceleration = acceleration;
  
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(modePin, OUTPUT);

  digitalWrite(this->dirPin, (this->currentDirection == CLOCKWISE?HIGH:LOW));
  this->enable(true);
  
}

void Stepper::step() {
  unsigned long currentTime = micros();
  if (this->stepsRemaining > 0 && this->nextStepTime < currentTime)  {
    if(currentTime - this->nextStepTime > 500) {
      Serial.write("Stepper overshot\n");
    }
    digitalWrite(this->stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->stepPin, LOW);

    this->stepsRemaining = this->stepsRemaining - 1;

    this->calculateNextStepTime(currentTime);
  }
}

void Stepper::step(long steps) {
  this->stepsRemaining += steps;
  this->calculateNextStepTime(micros());
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
  this->step();
}


void Stepper::calculateNextStepTime(unsigned long currentTime) {

  if(this->currentRPS <= this->maxRPS) {
    this->currentRPS += ((this->timeBetweenSteps / 1000000.0) * this->acceleration);
    // Serial.println((float)(this->currentRPS),5);
    this->timeBetweenSteps = (1.0f / (this->stepsPerRevolution * this->currentRPS)) * 1000000.0;
    //Serial.println((this->timeBetweenSteps));
  }
  this->nextStepTime = currentTime + this->timeBetweenSteps;
}


