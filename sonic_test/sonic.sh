#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL sonic.c -o sonic.o

avr-objcopy -O ihex sonic.o sonic.hex

sudo avrdude -c usbasp -p m16 -U flash:w:sonic.hex