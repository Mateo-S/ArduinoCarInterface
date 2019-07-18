#ifndef SERIAL_SENDER
#define SERIAL_SENDER
#include <libserialport.h>
#include <string>
#include <cstdint>

class SerialSender{
	public:
		SerialSender(const std::string&);
		~SerialSender();
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
		int updateSteering(uint16_t input);
		int updateBraking(uint16_t input);
		int updateThrottle(uint16_t input);
		
	private:
		static const int BAUD_RATE = 115200;
		static const int BITS = 8;
		static const int STOP_BITS = 1;
		static const int PARITY = SP_PARITY_NONE;
		static const int MAX_TIMEOUT = 100;
		std::string device;
		struct sp_port * port;
		struct OutputDriverMessage{ 
			uint8_t type;
			uint8_t padding;
			int16_t signal;
		} message;
		int sendMessage();
};

#endif
