#include <serialMessager.h>

int steeringPwmPin = 3;
int enginePwmPin = 5;
SerialMessageParser* messager;
double engineOutput;

void setup(){
  messager = new SerialMessageParser();

  pinMode(steeringPwmPin, OUTPUT);
  pinMode(enginePwmPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  messager->update();

  double steering = messager->getSteering();
  double braking = messager->getBraking();
  double throttle = messager->getThrottle();

  //merge throttle and braking into one value
  engineOutput = CarOutput(throttle, braking);

  //sending pwm to car
  analogWrite(steeringPwmPin, steering);
  analogWrite(enginePwmPin, engineOutput);
}

double CarOutput(double throttle, double braking) {
  engineOutput = ((double) throttle + (double) braking) / 2.0;
}
