#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL servo_test.c -o servo_test.o

avr-objcopy -O ihex servo_test.o servo_test.hex

sudo avrdude -c usbasp -p m16 -U flash:w:servo_test.hex