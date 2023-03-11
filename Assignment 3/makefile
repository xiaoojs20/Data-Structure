all: temperature.o temperature_lib.o
temperature.o: temperature.cpp temperature.h 
    g++ -std=c++11 -c temperature.cpp -o temperature.o
temperature_lib.o: temperature_lib.c temperature.h 
	g++ -std=c++11 -c temperature_lib.c -o temperature_lib.o


