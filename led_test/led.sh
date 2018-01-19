#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=1000000UL led.c -o led.o 

avr-objcopy -O ihex led.o led.hex

sudo avrdude -c usbasp -p m16 -U flash:w:led.hex -F