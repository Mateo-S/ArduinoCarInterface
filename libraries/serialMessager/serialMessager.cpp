#include "serialMessager.h"
#include <limits.h>

SerialMessageParser::SerialMessageParser() { //setup
  Serial.begin(9600);
}

SerialMessageParser::~SerialMessageParser() {
  Serial.end();
}

void SerialMessageParser::update() { //loop
  byte *serialInput = (byte*)&message;
  byte status = MSG_NONE;
  updated = false; 

  while (Serial.available()) { //If something is being sent to the Arduino via serial
    serialInput += Serial.readBytes(serialInput, 1);
    updated = true;
    Serial.println("bgjhgh");
  }

  if ((serialInput - (byte*)&message) != 4) {
    Serial.println("Message of invalid size, received. Data stream is corrupted!\n");
  }

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
  Serial.println(message.type);
  Serial.println(message.signal);
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
