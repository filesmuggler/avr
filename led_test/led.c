#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned int opoznienie;

void main(void)
{
    DDRA = 0xFF;

    opoznienie = 100;

    while (1)
    {

        PORTA |= (1 << 7);

        _delay_ms(opoznienie);

        PORTA &= ~(1 << 7);

        _delay_ms(opoznienie);
    }
}