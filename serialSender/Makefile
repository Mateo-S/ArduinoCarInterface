PORT := /dev/ttyACM0

all: test.cpp
	g++ test.cpp serialSender.cpp -lserialport && ./a.out $PORT
