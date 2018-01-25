#!/bin/bash

avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL led_interrupt.c -o led_interrupt.o

avr-objcopy -O ihex led_interrupt.o led_interrupt.hex

sudo avrdude -c usbasp -p m16 -U flash:w:led_interrupt.hex