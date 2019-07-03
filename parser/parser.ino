#include <serialMessager.h>
#include <Servo.h>
#include <servoController.h>

int steeringPwmPin = 9;
int enginePwmPin = 5;
int POTENTIOMETER_PIN = A0;
int POTENTIOMETER_UPPER_BOUND = 1024;
int steeringServoPosition = 0;
int engineServoPosition = 0;
Servo steeringServo;
Servo engineServo;

double engineOutput = 0;
double steeringOutput = 0;
double steering = 0;
double braking = 0;
double throttle = 0;
double oldEngine = 0;
double oldSteering = 0;

double ENGINE_MIN_VEL = 0.40;
double ENGINE_VEL_CONSTANT = 0.66;
int ENGINE_PERCENT_VEL_MAX_ACCEL = 50;

double STEERING_MIN_VEL = 0.40;
double STEERING_VEL_CONSTANT = 0.66;
int STEERING_PERCENT_VEL_MAX_ACCEL = 50;

SerialMessageParser* messager;
ServoController* engineServoController = new ServoController(ENGINE_MIN_VEL, ENGINE_VEL_CONSTANT, ENGINE_PERCENT_VEL_MAX_ACCEL, (double) engineServo.read());
ServoController* steeringServoController = new ServoController(STEERING_MIN_VEL, STEERING_VEL_CONSTANT, STEERING_PERCENT_VEL_MAX_ACCEL, (double) steeringServo.read());

void setup(){
  Serial.begin(9600);
  messager = new SerialMessageParser();
  engineServo.attach(enginePwmPin);
  steeringServo.attach(steeringPwmPin);
  engineServo.write(0);
  steeringServo.write(90);
  pinMode(POTENTIOMETER_PIN, INPUT);
  Serial.println("potLimit: "+analogRead(POTENTIOMETER_PIN)/POTENTIOMETER_UPPER_BOUND); 
}

// the loop function runs over and over again forever
void loop() {
  //get messages
  messager->update();
  //check max speed
  int potLimit = analogRead(POTENTIOMETER_PIN)/POTENTIOMETER_UPPER_BOUND;
  
  //get old values to compare later
  oldSteering = steeringOutput;
  oldEngine = engineOutput;

  //get steering, braking, throttle from jetson
  steering = messager->getSteering();
  braking = messager->getBraking();
  throttle = messager->getThrottle();

  //run jetson's values through smoothing library
  engineServoController->setFinalPos(carOutput(throttle, braking));
  steeringServoController->setFinalPos(steering);

  //update smooth path
  engineOutput = engineServoController->update();
  steeringOutput = steeringServoController->update();

  //potentiometer limiter
  if(engineOutput<=potLimit){ //if the calculated engine output is higher than the limit set by the potentiometer then cap it at potLimit
    engineOutput = potLimit;
  }

  Serial.print("Steering: ");
  Serial.println(steeringOutput);
  Serial.print("Engine: ");
  Serial.println(engineOutput);

  if(oldSteering != steering){
    steeringServo.write(steeringOutput);
  }
  if(oldEngine != engineOutput){
    engineServo.write(engineOutput);
  }
}

double carOutput(double throttle, double braking) {
  engineOutput = ((double) throttle + (double) braking) / 2.0;
}
