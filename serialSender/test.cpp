#include <iostream>
#include <thread>
// #include <chrono>
#include <unistd.h>
#include <limits.h>
#include "serialSender.h"
#include <iostream>

int main(int argc, char* argv[]){

    SerialSender* car;

    if(argc == 1){
        car = new SerialSender();
    } else if (argc == 2) {
        car = new SerialSender(std::string(argv[1]));
    }
    else {
        std::cerr << "Usage: ./a.out [device]" << std::endl; //on jetson device is /dev/ttyS0
        exit(1);
    }

    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(SHRT_MAX - (SHRT_MAX/10)); // 9/10 right
    std::cout << "Sending: " + (SHRT_MAX - (SHRT_MAX/10)) << "\n";
    
    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(SHRT_MIN - (SHRT_MIN/10)); // 9/10 left
    std::cout << "Sending: " + (SHRT_MIN - (SHRT_MIN/10)) << "\n";
    usleep(2000);
    // std::thread::sleep_for(std::chrono::seconds(2));
    car -> updateSteering(0); //middle
    std::cout << "Sending: " + 0 << "\n";
}