#include <serialMessager.h>
#include <Servo.h>

int steeringPwmPin = 9;
int enginePwmPin = 5;
int POTENTIOMETER_PIN = A0;
int POTENTIOMETER_UPPER_BOUND = 1024;
Servo steeringServo;
Servo engineServo;
int steeringServoPosition = 0;
int engineServoPosition = 0;

SerialMessageParser* messager;
double engineOutput = 0;
double steering = 0;
double braking = 0;
double throttle = 0;
double oldEngine = 0;
double oldSteering = 0;

void setup(){
  Serial.begin(9600);
  messager = new SerialMessageParser();

  steeringServo.attach(steeringPwmPin);
  engineServo.attach(enginePwmPin);
  pinMode(POTENTIOMETER_PIN, INPUT);
  Serial.println("potLimit: "+analogRead(POTENTIOMETER_PIN)/POTENTIOMETER_UPPER_BOUND); 
}

// the loop function runs over and over again forever
void loop() {
  messager->update();

  int potLimit = analogRead(POTENTIOMETER_PIN)/POTENTIOMETER_UPPER_BOUND;
  oldSteering = steering;
  oldEngine = engineOutput;

  steering = messager->getSteering();
  braking = messager->getBraking();
  throttle = messager->getThrottle();

  //merge throttle and braking into one value
  engineOutput = CarOutput(throttle, braking);

  //potentiometer limiter
  if(engineOutput<=potLimit){ //if the calculated engine output is higher than the limit set by the potentiometer then cap it at potLimit
    engineOutput = potLimit;
  }

  Serial.print("Steering: ");
  Serial.println(steering);
  Serial.print("Engine: ");
  Serial.println(engineOutput);

  if(oldSteering != steering){
    steeringServo.write(steering*180);
  }
  if(oldEngine != engineOutput){
    engineServo.write(engineOutput*180);
  }
}

double CarOutput(double throttle, double braking) {
  engineOutput = ((double) throttle + (double) braking) / 2.0;
}
