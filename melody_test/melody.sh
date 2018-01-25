#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL melody.c -o melody.o

avr-objcopy -O ihex melody.o melody.hex

sudo avrdude -c usbasp -p m16 -U flash:w:melody.hex