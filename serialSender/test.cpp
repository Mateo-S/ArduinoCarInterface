#include <iostream>
#include <thread>
// #include <chrono>
#include <unistd.h>
#include <limits.h>
#include "serialSender.h"

SerialSender* car;

void reset(){ //takes all values back to zero
    car -> updateSteering(0);
    car -> updateThrottle(0);
    car -> updateBraking(0);
}

int main(int argc, char* argv[]){


    if(argc == 1){
        car = new SerialSender();
    } else if (argc == 2) {
        car = new SerialSender(std::string(argv[1]));
    }
    else {
        std::cerr << "Usage: ./a.out [device]" << std::endl; //on jetson device is /dev/ttyS0
        exit(1);
    }

    //STEERING  Max --> Center --> Min --> Center --> Min --> Max
    usleep(2500000);
    car -> updateSteering(SHRT_MAX); // 9/10 right
    std::cout << "Steering Max: " << SHRT_MAX << "\n";

    usleep(2500000);
    car -> updateSteering(0); //middle
    std::cout << "Steering Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateSteering(SHRT_MIN); // 9/10 left
    std::cout << "Steering Min: " << SHRT_MIN << "\n";
    
    usleep(2500000);
    car -> updateSteering(0); //middle
    std::cout << "Steering Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateSteering(SHRT_MIN); // 9/10 left
    std::cout << "Steering Min: " << SHRT_MIN << "\n";

    usleep(2500000);
    car -> updateSteering(SHRT_MAX); // 9/10 right
    std::cout << "Steering Max: " << SHRT_MAX << "\n";
    
    //THROTTLE  Max --> Center --> Min --> Center --> Min --> Max
    usleep(2500000);
    car -> updateThrottle(SHRT_MAX);
    std::cout << "Throttle Max: " << SHRT_MAX << "\n";
    
    usleep(2500000);
    car -> updateThrottle(0); 
    std::cout << "Throttle Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateThrottle(SHRT_MIN);
    std::cout << "Throttle Min: " << SHRT_MIN << "\n";
    
    usleep(2500000);
    car -> updateThrottle(0); 
    std::cout << "Throttle Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateThrottle(SHRT_MIN);
    std::cout << "Throttle Min: " << SHRT_MIN << "\n";

    usleep(2500000);
    car -> updateThrottle(SHRT_MAX);
    std::cout << "Throttle Max: " << SHRT_MAX << "\n";

    //BRAKING  Max --> Center --> Min --> Center --> Min --> Max
    usleep(2500000);
    car -> updateBraking(SHRT_MAX);
    std::cout << "Braking Max: " << SHRT_MAX << "\n";
    
    usleep(2500000);
    car -> updateBraking(0); 
    std::cout << "Braking Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateBraking(SHRT_MIN);
    std::cout << "Braking Min: " << SHRT_MIN << "\n";
    
    usleep(2500000);
    car -> updateBraking(0); 
    std::cout << "Braking Center: " << 0 << "\n";

    usleep(2500000);
    car -> updateBraking(SHRT_MIN);
    std::cout << "Braking Min: " << SHRT_MIN << "\n";

    usleep(2500000);
    car -> updateBraking(SHRT_MAX);
    std::cout << "Braking Max: " << SHRT_MAX << "\n";

    //Out of bounds over steering
    usleep(2500000);
    car -> updateSteering(SHRT_MAX+1);
    std::cout << "Steering out of bounds max: " << SHRT_MAX+1 << "\n";

    //Out of bounds over throttle
    usleep(2500000);
    car -> updateThrottle(SHRT_MAX+1);
    std::cout << "Throttle out of bounds max: " << SHRT_MAX+1 << "\n";

    //Out of bounds under steering
    usleep(2500000);
    car -> updateSteering(SHRT_MIN-1);
    std::cout << "Steering out of bounds min: " << SHRT_MIN-1 << "\n";

    //Out of bounds under throttle
    usleep(2500000);
    car -> updateThrottle(SHRT_MIN-1);
    std::cout << "Throttle out of bounds min: " << SHRT_MIN-1 << "\n";
}