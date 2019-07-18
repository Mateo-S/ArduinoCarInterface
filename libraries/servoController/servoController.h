#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include "Arduino.h"
#include <Servo.h>

//Average Duty Cycle by command, <Motor to control>_<Reverse or Normal>_<Neutral, forward, or back>
const double SERVO_NORMAL_NEUTRAL = 9.285;
const double SERVO_NORMAL_RIGHT = 6.63;
const double SERVO_NORMAL_LEFT = 11.9;
const double SERVO_REVERSE_NEUTRAL = 8.8;
const double SERVO_REVERSE_RIGHT = 11.4;
const double SERVO_REVERSE_LEFT = 6.145;
const double SERVO_PERCENT_VEL_MAX_ACCEL = 0.50;

const double ENGINE_NORMAL_NEUTRAL = 9.04;
const double ENGINE_NORMAL_RIGHT = 6.14;
const double ENGINE_NORMAL_LEFT = 12.0;
const double ENGINE_REVERSE_NEUTRAL = 9.035;
const double ENGINE_REVERSE_RIGHT = 11.9;
const double ENGINE_REVERSE_LEFT = 6.265;
const double ENGINE_PERCENT_VEL_MAX_ACCEL = 0.50;


class ServoController{
public:

    enum SERVO_TYPE {
        STEERING,
        ENGINE
    };

    ServoController(SERVO_TYPE stype, int pin);
    ~ServoController();

    double update();
    double getDeltaDuty();
    double getFinalPos();
    void setFinalPos(double scaleFactor);
    void setTrim(double);
    // int getPercentVelMaxAccel();
    double getMaxAccelV();
    void setDeltaDuty (double percent_change);
    void setMaxAccelV(double, double, int);
    void setDiffMaxAndCurrent (double, double);
    double getDiffMaxAndCurrent();
    bool isReverse();
    void setReverse(bool);
    // struct servoControler{
    //     double initialPos;
    //     double finalPos;
    // };
private:
    Servo servo; 
    ServoController::SERVO_TYPE stype;
    double myPos;
    double finalPos;
    double initialPos;
    double deltaDuty;
    double diffMaxAndCurrent;
    bool inReverse;
    double MAX_DELTA_DUTY_SCALE;
    double MIN_DUTY_CYCLE;
    double MAX_DUTY_CYCLE;
    double NEUTRAL_DUTY_CYCLE;
    double TRIM;
};


// function gets to vars:
// final pos, delta duty
#endif