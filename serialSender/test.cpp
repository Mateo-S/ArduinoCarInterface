#include <iostream>
#include <thread>
// #include <chrono>
#include <unistd.h>
#include <limits.h>
#include "serialSender.h"

int main(int argc, char* argv[]){

    SerialSender* car;

    if(argc == 1){
        car = new SerialSender();
    } else if (argc == 2) {
        car = new SerialSender(std::string(argv[1]));
    }
    else {
        std::cerr << "Usage: ./test [device]" << std::endl;
        exit(1);
    }

    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(SHRT_MAX - (SHRT_MAX/10)); //right
    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(SHRT_MIN - (SHRT_MIN/10)); //left
    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(0); //middle
}