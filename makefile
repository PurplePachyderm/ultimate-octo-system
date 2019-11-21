test:
	g++ main.cpp -Wall -lwiringPi -std=c++11


hex:
		avr-gcc -Os -DF_CPU=8000000 -mmcu=attiny85 -c slave.c
		avr-gcc -DF_CPU=8000000 -mmcu=attiny85 -o slave.elf slave.o
		avr-objcopy -O ihex slave.elf slave.hex
		rm slave.o
		rm slave.elf
