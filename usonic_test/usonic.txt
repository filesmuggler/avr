#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// definicja pinów uzywanych w projekcie
#define Red_diode 6
#define Green_diode 7
#define Button_pin 5
#define Servo_pin 7

// globalna zmienna do liczenia przeładowań
volatile uint8_t tot_overflow;

// inicjalizacja timera
void timer0_init()
{
    // włączenie timera z przeskalowaniem równym 256
    TCCR0 |= (1 << CS02);

    // inicjalizacja licznika
    TCNT0 = 0;

    // umożliwienie przerwania przeładowań
    TIMSK |= (1 << TOIE0);

    // włączenie gloablnych przerwań
    sei();

    // inicjalizacja licznika przeładowań
    tot_overflow = 0;
}

// TIMER0 przeładowanie usługi przerwania
// wykonywana kiedy TCNT0 sie przeładuje
ISR(TIMER0_OVF_vect)
{
    // liczenie przeładowań
    tot_overflow++;
}

int main(void)
{
    // inicjalizacja pinów
    DDRA = 0b11000000;
    DDRD = 0xFF;

    // wywołanie funkcji z przerwaniami
    timer0_init();

    // pętla głowna
    while (1)
    {
        // polling
        // jeśli przycisk wciśniety, włącz led i servo
        if (PINA & (1 << Button_pin))
        {
            PORTA |= (1 << Red_diode); // włącza led
            PORTA &= ~(1 << Green_diode); // włącza led
            PORTD |= (1 << Servo_pin); // włącza servo - nie działa
        }
        else
        {
            PORTA &= ~(1 << Red_diode);   // wyłącza led
            PORTA |= (1 << Green_diode); // włącza led
            PORTD &= ~(1 << Servo_pin);     // wyłącza servo - nie działa
        }

        // przerwania
        // sprawdza ilosc przeladowan procesora
        if (tot_overflow >= 100) //'>=' ponieważ '==' mogłoby nigdy nie spotkać warunku
        {
            if (TCNT0 > 53)
            {
                PORTA |= (1 << Red_diode); // włącza led
                _delay_ms(100);             // nie powinno sie stosować delay w przerwaniu ale to dla demonstracji
                PORTA &= ~(1 << Red_diode); //wyłącza led
                TCNT0 = 0;        // reset licznika
                tot_overflow = 0; // reset licznika przeładowań
            }
        }
    }
}