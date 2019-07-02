
ARDUINO := arduino-cli
TARGET := arduino:avr:uno
SKETCH := parser

all:
	$(ARDUINO) compile $(SKETCH) --fqbn $(TARGET) 
