#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define Red_diode PINB7
#define Buzzer_pin PINA0
#define Trigger_pin1 PIND1
#define Trigger_pin2 PIND4

unsigned latency;
int frequency;
static volatile int pulse = 0; //interger  to access all though the program
static volatile int i = 0;     // interger  to access all though the program

void main(void)
{
    latency = 200;
    frequency = 440;

    DDRB = 0b10000000;
    DDRD = 0b01001000;
    PORTD = 0xFF;

    GICR |= (1 << INT0);   //enabling interrupt at interrupt0
    MCUCR |= (1 << ISC00); //setting interrupt triggering logic change

    TCCR1A = 0;

    int16_t countA = 0; // storing digital output

    sei(); /* enable global interrupts */

    while (1)
    {
        PORTD |= (1 << Trigger_pin1);
        _delay_us(10);
        PORTD &= ~(1 << Trigger_pin1);

        countA = pulse / 58;

        if (countA>0)
        {
            PORTB |= (1 << Red_diode); // zmiana wartosci logicznych
            _delay_ms(latency);
            PORTB &= ~(1 << Red_diode);
        }
    }
}

 ISR(INT0_vect)
        {
            if (i == 1)
            {
                TCCR1B = 0;    //disabling counter
                pulse = TCNT1; //count memory is updated to integer
                TCNT1 = 0;     //resetting the counter memory
                i = 0;
            }
            if (i == 0)
            {
                TCCR1B |= (1 << CS10);
                i = 1;
            }
        }