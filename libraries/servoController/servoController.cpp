#include "servoController.h"

ServoController::ServoController(
    ServoController::SERVO_TYPE sty, int pin) {
        stype = sty;
        inReverse = false;
        TRIM = 0;

    if (stype == ENGINE) {
        MIN_DUTY_CYCLE = ENGINE_NORMAL_LEFT;
        MAX_DUTY_CYCLE = ENGINE_NORMAL_RIGHT;
        NEUTRAL_DUTY_CYCLE = ENGINE_NORMAL_NEUTRAL + TRIM;
        MAX_DELTA_DUTY_SCALE = ENGINE_PERCENT_VEL_MAX_ACCEL;
    }else if(stype == STEERING){
        MIN_DUTY_CYCLE = SERVO_NORMAL_LEFT;
        MAX_DUTY_CYCLE = SERVO_NORMAL_RIGHT;
        NEUTRAL_DUTY_CYCLE =SERVO_NORMAL_NEUTRAL + TRIM;
        MAX_DELTA_DUTY_SCALE = SERVO_PERCENT_VEL_MAX_ACCEL;
    }
    
    servo.attach(pin);

    initialPos = servo.read();
    myPos = initialPos;
}
double ServoController::getDeltaDuty(){
    return deltaDuty;
}
// double ServoController::getMinVel(){
// //     return MIN_VEL;
// }
// double ServoController:: getMyPos(){
//     return myPos;
// }
// double ServoController:: getInitialPos(){
//     return initialPos;
// }
double ServoController:: getFinalPos(){
    return finalPos;
}
// double ServoController::getVelConstant(){
//     return VEL_CONSTANT;
// }
bool ServoController::isReverse(){
    return inReverse;
}
// int ServoController::getPercentVelMaxAccel(){
//     return PERCENT_VEL_MAX_ACCEL;
// }K
double ServoController::getMaxAccelV() {
    return MAX_DELTA_DUTY_SCALE;
}

void ServoController :: setDeltaDuty(double percent_change){
    const double SCALE_POS = MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE;
    const double SCALE_NEG = NEUTRAL_DUTY_CYCLE - MIN_DUTY_CYCLE;
    if (myPos > NEUTRAL_DUTY_CYCLE) {
        deltaDuty = percent_change * SCALE_POS;
    } else {
        deltaDuty = percent_change * SCALE_NEG;
    }
}
void ServoController :: setDiffMaxAndCurrent (double mav, double mp){
    diffMaxAndCurrent = abs(mav-mp);
}
void ServoController :: setFinalPos(double scaleFactor){

    if (abs(scaleFactor) > 1.0) { 
        return; 
    }

    const double SCALE_POS = MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE;
    const double SCALE_NEG = NEUTRAL_DUTY_CYCLE - MIN_DUTY_CYCLE;
    double fp = NEUTRAL_DUTY_CYCLE + (scaleFactor > 0 ? scaleFactor * SCALE_POS : scaleFactor * SCALE_NEG);
    // setMaxAccelV(myPos,fp,getPercentVelMaxAccel());
    // setDiffMaxAndCurrent(getMaxAccelV(),getMyPos());
    setDeltaDuty(  abs(myPos - finalPos) / (MAX_DUTY_CYCLE - MIN_DUTY_CYCLE)  );
}
// void ServoController :: setInitialPos(double ip){
//     initialPos = ip;
// }
void ServoController :: setReverse(bool rev){
    inReverse = rev;
    if (inReverse) {
        if (stype == ENGINE) {
            MIN_DUTY_CYCLE = ENGINE_REVERSE_LEFT;
            MAX_DUTY_CYCLE = ENGINE_REVERSE_RIGHT;
            NEUTRAL_DUTY_CYCLE = ENGINE_REVERSE_NEUTRAL + TRIM;
        } else if(stype == STEERING){
            MIN_DUTY_CYCLE = SERVO_REVERSE_LEFT;
            MAX_DUTY_CYCLE = SERVO_REVERSE_RIGHT;
            NEUTRAL_DUTY_CYCLE = SERVO_REVERSE_NEUTRAL + TRIM;
        }
    }
    else {
if (stype == ENGINE) {
            MIN_DUTY_CYCLE = ENGINE_NORMAL_LEFT;
            MAX_DUTY_CYCLE = ENGINE_NORMAL_RIGHT;
            NEUTRAL_DUTY_CYCLE = ENGINE_NORMAL_NEUTRAL + TRIM;
        } else if(stype == STEERING){
            MIN_DUTY_CYCLE = SERVO_NORMAL_LEFT;
            MAX_DUTY_CYCLE = SERVO_NORMAL_RIGHT;
            NEUTRAL_DUTY_CYCLE = SERVO_NORMAL_NEUTRAL + TRIM;
        }
    }
}

// New trim will not be applied until shift in gears (fwd/rev)
void ServoController :: setTrim(double scale){
    const double SCALE_POS = MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE;
    const double SCALE_NEG = NEUTRAL_DUTY_CYCLE - MIN_DUTY_CYCLE;
    TRIM = (scale > 0 ? scale * SCALE_POS : scale * SCALE_NEG);
}
double ServoController :: getDiffMaxAndCurrent(){
    return diffMaxAndCurrent;
}
// struct ServoController :: servoController(double ip, double fp){
//     initialPos = ip;
//     finalPos = fp;
//     myPos=ip;
//     setMaxAccelV(ip,fp,PERCENT_VEL_MAX_ACCEL);
//     setDiffMaxAndCurrent(maxAccelV,ip);
//     setDeltaV(MIN_VEL,VEL_CONSTANT,diffMaxAndCurrent);
// }
double ServoController:: update(){
    const double SCALE_POS = MAX_DUTY_CYCLE - NEUTRAL_DUTY_CYCLE;
    const double SCALE_NEG = NEUTRAL_DUTY_CYCLE - MIN_DUTY_CYCLE;

    if((int) myPos != (int) getFinalPos()){
        if(myPos < getFinalPos()){
            myPos += getDeltaDuty();
            double absDeltaPos = abs(finalPos - myPos);
            if (absDeltaPos > MAX_DELTA_DUTY_SCALE * SCALE_POS) {
                // deltaDuty should be MAX_DELTA_DUTY_SCALE * SCALE_POS
            }
            else {
                // deltaDuty should be absDeltaPos
            }
        }
        else{
            myPos -= getDeltaDuty();
            double absDeltaPos = abs(finalPos - myPos);
            if (absDeltaPos > MAX_DELTA_DUTY_SCALE * SCALE_NEG) {
                // deltaDuty should be MAX_DELTA_DUTY_SCALE * SCALE_NEG
            }
            else {
                // deltaDuty should be absDeltaPos
            }
        }

    // figure out how much the duty cycle should change next update
    // setDiffMaxAndCurrent(getMaxAccelV(),myPos);

    // Set the change to that percentage
    // setDeltaDuty(getMinVel(),getVelConstant(),getDiffMaxAndCurrent());
    return myPos;
    }
}