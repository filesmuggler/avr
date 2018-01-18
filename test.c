#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>	

unsigned int i, opoznienie, opoznienie2, petla;

void main(void)
{
	DDRB=0xFF; //wszystkie bity z rejestru B na output
	
	opoznienie = 1000;
	opoznienie2 = 100;
	petla = 20;

	while(1)
	{
		_delay_ms(opoznienie);

		PORTB |=(1<<7);		// zmiana wartosci logicznych

		_delay_ms(opoznienie2);

		PORTB &=~(1<<7);
	}
}
	
