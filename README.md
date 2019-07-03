# ArduinoCarInterface

### Arduino code to interface with a Jetson Nano for use on an autonomous RC car

To compile the arduino sketch run: ~~`arduino-cli compile parser --fqbn arduino:avr:uno`~~ `make`

To upload the arduino sketch run: `sudo chmod 666 /dev/ttyACM* && arduino-cli upload parser --fqbn arduino:avr:uno -p /dev/ttyACM*`
