#include "serialSender.h"
#include <iostream>

SerialSender::SerialSender(const std::string& dev){
	device = dev;
	if(sp_get_port_by_name(dev.c_str(), &port) != SP_OK){
		std::cerr << "device not found" << std::endl;
	}
	int modeflags = SP_MODE_READ;
	modeflags |= (int)SP_MODE_WRITE;
	if(sp_open(port, (sp_mode)modeflags) != SP_OK){
		std::cerr << "could not open port" << std::endl;
	}
	 if(sp_set_baudrate(port, BAUD_RATE) != SP_OK){
		 std::cerr << "cant set baudrate" << std::endl;
	 }
	 if(sp_set_bits(port, BITS) != SP_OK){
		 std::cerr << "cant set bits" << std::endl;
	 }
	 if(sp_set_parity(port, (sp_parity)PARITY) != SP_OK){
		 std::cerr << "cant set parity" << std::endl;
	 }
	 if(sp_set_stopbits(port, STOP_BITS) != SP_OK){
		 std::cerr << "cant set stop bits" << std::endl;
	 }



}

SerialSender::~SerialSender(){
	sp_close(port);
	if(port != NULL){
		sp_free_port(port);
	}
}

int SerialSender::sendMessage(){
	//send OutPutDriver message
	sp_blocking_write(port, (void*) &message, sizeof(struct OutputDriverMessage), MAX_TIMEOUT);

	uint8_t ack;
	sp_blocking_read(port, (void*) &ack, sizeof(uint8_t), MAX_TIMEOUT);

	struct {
		uint8_t messageType ;
		uint8_t messageSignal;
		double steering;
		double engine;
	} debug;
	sp_blocking_read(port, (void*) &debug, 2 * sizeof(double), MAX_TIMEOUT);Type


	std::cout << "Message Type: " << debug.messageType << std::endl;
	std::cout << "Message Signal: " << debug.messageSignal << std::endl;
	std::cout << "Steering status: " << debug.steering << std::endl;
	std::cout << "Engine status:   " << debug.engine << std::endl;
	
	return (int) ack;
}

int SerialSender::updateSteering(uint16_t input){
	message.type = STEERING;
	message.padding = 0;
	message.signal = input;

	return sendMessage();
}

int SerialSender::updateThrottle(uint16_t input){
	message.type = THROTTLE;
	message.padding = 0;
	message.signal = input;

	return sendMessage();
}

int SerialSender::updateBraking(uint16_t input){
	message.type = BRAKING;
	message.padding = 0;
	message.signal = input;

	return sendMessage();
}
