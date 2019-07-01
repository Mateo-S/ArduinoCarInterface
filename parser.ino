#include <serialMessager.h>

int steeringPwmPin = 3;
int enginePwmPin = 5;
SerialMessageParser* messager;


void setup(){
  messager = new SerialMessageParser();

  pinMode(steeringPwmPin, OUTPUT);
  pinMode(enginePwmPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  messager->update();

  double steering = messager->getSteering();
  double engine = messager->getEngine();

  analogWrite(steeringPwmPin, steering);
  analogWrite(enginePwmPin, engine);
}
