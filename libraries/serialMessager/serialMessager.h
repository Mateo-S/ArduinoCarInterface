#ifndef SERIAL_MESSAGER_H
#define SERIAL_MESSAGER_H

#include "Arduino.h"

class SerialMessageParser{
public:
    SerialMessageParser();
    ~SerialMessageParser();
    void update();
    double getThrottle();
    double getBraking();
    double getSteering();
    bool isUpdated();

    enum MessageType {
        THROTTLE = 0,
        BRAKING,
        STEERING        
    };

    enum MessageStatus {
        MSG_NONE = 0,
        MSG_OK,
        MSG_BAD = 0xFF
    };
    
    struct InputDriverMessage{ //individual messages that come from the nano
        uint8_t type;
        uint8_t padding;
        int16_t signal;
    } message;

private:
    bool updated;
    double steering_output;
    double braking_output;
    double throttle_output;
    // double calcCarOutput(int16_t throttle, int16_t braking);
    struct ParsedDriverMesssage{ //3 values that come from the nano
    double steering;
    double throttle;
    double braking;
  } parsed;

};

#endif