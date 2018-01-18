#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

unsigned int opoznienie;
int czestotliwosc[8] = {22.5, 55, 110, 220, 440, 880, 1760, 3520};

void main(void)
{
    /*
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRD = 0b01001000;

    czestotliwosc = 440;
    opoznienie = 1000/(2*440);
    
    while(1){
        _delay_ms(opoznienie);
        PORTA |=(1<<0);
        _delay_ms(opoznienie);
        PORTA &=~(1<<0);
    }
    */
    /*DDRA = 0xFF;
    DDRB = 0xFF;
    DDRD = 0b01001000;

    
    while(1){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 1000; j++){
                    opoznienie = 1000/(2*czestotliwosc[i]);
                    _delay_ms(opoznienie);
                    PORTA |=(1<<0);
                    _delay_ms(opoznienie);
                    PORTA &=~(1<<0);
                }
            }
    }
    */
    DDRA = 0xFF;
    DDRB = 0xFF;
    DDRD = 0b01001000;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            opoznienie = 1000 / (2 * czestotliwosc[i]);
            _delay_ms(opoznienie);
            PORTA |= (1 << 0);
            _delay_ms(opoznienie);
            PORTA &= ~(1 << 0);
        }
        PORTB |=(1<<7);		// zmiana wartosci logicznych
        _delay_ms(1000);
        PORTB &=~(1<<7);

    }
}
