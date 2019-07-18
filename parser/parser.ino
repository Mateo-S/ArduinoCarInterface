#include <serialMessager.h>

#include <Servo.h>

#include <servoController.h>

const int STEERING_PWM_PIN = 9;
const int ENGINE_PWM_PIN = 5;
const int POTENTIOMETER_PIN = A0;
const int POTENTIOMETER_UPPER_BOUND = 1024;
int steeringServoPosition = 0;
int engineServoPosition = 0;

//Old and current values
double engineOutput = 0;
double steeringOutput = 0;
double steering = 0;
double braking = 0;
double throttle = 0;
double oldEngine = 0;
double oldSteering = 0;
double pwmSteeringOutput = 0;
double pwmEngineOutput = 0;

//PID consts
const double ENGINE_MIN_VEL = 0.40;
const double ENGINE_VEL_CONSTANT = 0.66;

const double STEERING_MIN_VEL = 0.40;
const double STEERING_VEL_CONSTANT = 0.66;

//Custom objects
SerialMessageParser * messager;
ServoController * engineServoController;
ServoController * steeringServoController;

void setup() {
    Serial.begin(9600);
    messager = new SerialMessageParser();
    // engineServoController = new ServoController(ENGINE_MIN_VEL, ENGINE_VEL_CONSTANT, ENGINE_PERCENT_VEL_MAX_ACCEL, ENGINE_PWM_PIN);
    engineServoController = new ServoController(ServoController::ENGINE, ENGINE_PWM_PIN);
    // steeringServoController = new ServoController(STEERING_MIN_VEL, STEERING_VEL_CONSTANT, STEERING_PERCENT_VEL_MAX_ACCEL, STEERING_PWM_PIN);
    steeringServoController = new ServoController(ServoController::STEERING, STEERING_PWM_PIN);
    // Set servos to neutral value
    engineServoController -> setFinalPos(0.0);
    steeringServoController -> setFinalPos(0.0);
    // Force the servos to update themselves to the new position
    engineOutput = engineServoController -> update();
    steeringOutput = steeringServoController -> update();

    pinMode(POTENTIOMETER_PIN, INPUT);
    Serial.println("potLimit: " + analogRead(POTENTIOMETER_PIN) / POTENTIOMETER_UPPER_BOUND);
}
    void loop() {
      //get messages
      messager -> update();
      //check max speed
      int potLimit = analogRead(POTENTIOMETER_PIN) / POTENTIOMETER_UPPER_BOUND;

      //get old values to compare later
      oldSteering = steeringOutput;
      oldEngine = engineOutput;

      //get steering, braking, throttle from jetson
      steering = messager -> getSteering();
      braking = messager -> getBraking();
      throttle = messager -> getThrottle();

      //run jetson's values through smoothing library
      engineServoController -> setFinalPos(carOutput(throttle, braking));
      steeringServoController -> setFinalPos(steering);

      //update smooth path
      engineOutput = engineServoController -> update();
      steeringOutput = steeringServoController -> update();

      //potentiometer limiter
      if (engineOutput <= potLimit) { //if the calculated engine output is higher than the limit set by the potentiometer then cap it at potLimit
        engineOutput = potLimit;
      }

      Serial.print("Steering: ");
      Serial.println(steeringOutput);
      Serial.print("Engine: ");
      Serial.println(engineOutput);
    }

    double carOutput(double throttle, double braking) {
      engineOutput = ((double) throttle + (double) braking) / 2.0;
    }