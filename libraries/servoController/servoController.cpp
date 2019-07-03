#include "servoController.h"

ServoController::ServoController(double minVel, 
    double velConstant,
     int percentVelMaxAccel,
      double ip):

    MIN_VEL(minVel),
    VEL_CONSTANT(velConstant),
    PERCENT_VEL_MAX_ACCEL(percentVelMaxAccel){
    initialPos = ip;
    myPos=ip;
}
double ServoController::getDeltaV(){
    return deltaV;
}
double ServoController::getMinVel(){
    return MIN_VEL;
}
double ServoController:: getMyPos(){
    return myPos;
}
double ServoController:: getInitialPos(){
    return initialPos;
}
double ServoController:: getFinalPos(){
    return finalPos;
}
double ServoController::getVelConstant(){
    return VEL_CONSTANT;
}
int ServoController::getPercentVelMaxAccel(){
    return PERCENT_VEL_MAX_ACCEL;
}
double ServoController::getMaxAccelV() {
    return maxAccelV;
}
void ServoController::setMaxAccelV(double ip, double fp, int pvma){
    maxAccelV = ip +(fp-ip)*pvma/100;
}
void ServoController :: setDeltaV(double mv, double vc, double dmac){
    maxAccelV = mv+vc/dmac;
}
void ServoController :: setDiffMaxAndCurrent (double mav, double mp){
    diffMaxAndCurrent = abs(mav-mp);
}
void ServoController :: setFinalPos(double fp){
    finalPos = fp;
    setMaxAccelV(getMyPos(),fp,getPercentVelMaxAccel());
    setDiffMaxAndCurrent(GetMaxAccelV(),getMyPos());
    setDeltaV(getMinVel(),getVelConstant(),getDiffMaxAndCurrent());
}
void ServoController :: setInitialPos(double ip){
    initialPos = ip;
}
void ServoController :: setMyPos(double mp){
    myPos = mp;
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
    if((int) getMyPos() != (int) getFinalPos()){
        if(getMyPos()<getFinalPos()){
            setMyPos(getMyPos()+getDeltaV());
        }
        else{
            setMyPos(getMyPos()-getDeltaV());
        }
    setDiffMaxAndCurrent(getMaxAccelV(),getMyPos());
    setDeltaV(getMinVel(),getVelConstant(),getDiffMaxAndCurrent());
    return getMyPos();
    }
}