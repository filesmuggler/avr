#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL buzzer.c -o buzzer.o 

avr-objcopy -O ihex buzzer.o buzzer.hex

sudo avrdude -c usbasp -p m16 -U flash:w:buzzer.hex