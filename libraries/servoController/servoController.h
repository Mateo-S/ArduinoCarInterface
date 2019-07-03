#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include "Arduino.h"
#include <Servo.h>
class ServoController{
public:
    ServoController(double& minVel, double& velConstant, int& percentVelMaxAccel, double ip);
    ~ServoController();
    double update();
    double getDeltaV();
    double getMyPos();
    double getInitialPos();
    double getFinalPos();
    void setInitialPos(double);
    void setFinalPos(double);
    void setMyPos(double);
    double getMinVel();
    double getVelConstant();
    int getPercentVelMaxAccel();
    double getMaxAccelV();
    void setDeltaV (double, double, double);
    void setMaxAccelV(double, double, int);
    void setDiffMaxAndCurrent (double, double);
    double getDiffMaxAndCurrent();
    // struct servoControler{
    //     double initialPos;
    //     double finalPos;
    // };
private:
    Servo servo; 
    double myPos;
    double finalPos;
    double initialPos;
    double maxAccelV;
    double deltaV;
    double diffMaxAndCurrent;
    const double MIN_VEL;
    const double VEL_CONSTANT;
    const int PERCENT_VEL_MAX_ACCEL; 
};

#endif