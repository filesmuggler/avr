#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned int opoznienie_ciszy, opoznienie_dzwieku;

void main(void){
    DDRA = 0xFF;
    DDRB = 0xFF;

    opoznienie_dzwieku = 1000;
    opoznienie_ciszy = 100;

    while(1){
        _delay_ms(opoznienie_ciszy);

        PORTA |=(1<<0);
        PORTB |=(1<<7);		// zmiana wartosci logicznych


        _delay_ms(opoznienie_dzwieku);

        PORTA &=~(1<<0);
        PORTB &=~(1<<7);
    }
}