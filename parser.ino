#include <serialMessager.h>

int steeringPwmPin = 3;
int enginePwmPin = 5;
int POTENTIOMETER_PIN = A0;
int POTENTIOMETER_UPPER_BOUND = 1024;

SerialMessageParser* messager;
double engineOutput;

void setup(){
  messager = new SerialMessageParser();

  pinMode(steeringPwmPin, OUTPUT);
  pinMode(enginePwmPin, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);

  int potLimit = analogRead(POTENTIOMETER_PIN)/POTENTIOMETER_UPPER_BOUND;
}

// the loop function runs over and over again forever
void loop() {
  messager->update();

  double steering = messager->getSteering();
  double braking = messager->getBraking();
  double throttle = messager->getThrottle();

  //merge throttle and braking into one value
  engineOutput = CarOutput(throttle, braking);

  //potentiometer limiter
  if(engineOutput<=potLimit){ //if the calculated engine output is higher than the limit set by the potentiometer then cap it at potLimit
    engineOutput = potLimit;
  }

  //sending pwm to car
  analogWrite(steeringPwmPin, steering);
  analogWrite(enginePwmPin, engineOutput);
}

double CarOutput(double throttle, double braking) {
  engineOutput = ((double) throttle + (double) braking) / 2.0;
}
