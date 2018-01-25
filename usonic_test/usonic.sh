#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL usonic.c -o usonic.o

avr-objcopy -O ihex usonic.o usonic.hex

sudo avrdude -c usbasp -p m16 -U flash:w:usonic.hex