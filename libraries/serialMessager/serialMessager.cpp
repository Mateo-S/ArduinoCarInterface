#include "serialMessager.h"
#include <limits.h>

SerialMessageParser::SerialMessageParser() { //setup
  Serial.begin(9600);
}

SerialMessageParser::~SerialMessageParser() {
  Serial.end();
}

void SerialMessageParser::update() { //loop
  byte serialInput[4];
  byte status = MSG_NONE;

  if (Serial.available() > 0) { //If something is being sent to the Arduino via serial
    Serial.readBytes(serialInput, 4);
    updated = true;
  } else {
   updated = false; 
  }



  message = * ((struct InputDriverMessage * ) serialInput);

  if (message.type == THROTTLE) { //if it's a steering message
    parsed.throttle = message.signal > 0 ? message.signal/SHRT_MAX : message.signal/SHRT_MIN;
    status = MSG_OK;
  } else if (message.type == BRAKING) {
    parsed.braking = message.signal > 0 ? message.signal/SHRT_MAX : message.signal/SHRT_MIN;
    status = MSG_OK;
  } else if (message.type == STEERING) {
    parsed.steering = message.signal > 0 ? message.signal/SHRT_MAX : message.signal/SHRT_MIN;
    status = MSG_OK;
  } else { // If the message is unrecognized
    status = MSG_BAD;
  }

  // Serial.write(status);
  Serial.write(message);
}

bool SerialMessageParser::isUpdated() {
  return updated;
}

double SerialMessageParser::getSteering() {
  return steering_output;
}

double SerialMessageParser::getThrottle() {
  return throttle_output;
}

double SerialMessageParser::getBraking(){
  return braking_output;
}

// double SerialMessageParser::calcCarOutput(int16_t throttle, int16_t braking) {
//   engine_output = ((double) throttle + (double) braking) / 2.0;
// }