#ArduinoCarInterface
Arduino Sketch and libs to interface arduino to jetson nano

To compile the arduino sketch run: `arduino-cli compile parser --fqbn arduino:avr:uno`
To upload the arduino sketch run: `sudo chmod 666 /dev/ttyACM0 && arduino-cli upload parser --fqbn arduino:avr:uno -p /dev/ttyACM0`
