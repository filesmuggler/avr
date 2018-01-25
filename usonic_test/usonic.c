#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// piny użyte w projekcie
#define Red_diode PINB7
#define Buzzer_pin PINA0
#define Trigger_pin1 PIND1
#define Trigger_pin2 PIND4

// opóźnienie
unsigned opoznienie;
// częstotliwość dzwieku
int czestotliwosc;
// czy działa
unsigned char working;
// do narastającego zbocza
unsigned char rising_edge;
// wartość timera
uint16_t timer_value;
//dystans w cm
int distance_cm;
// error
uint8_t error;

// funkcja właczenia czujnika
void Send_signal(void);
// włączenie przerwan
void Initialize_external_interrupt (void);
// włączenie timera
void Initialize_timer0 (void);


ISR (TIMER0_OVF_vect)
{
	if(rising_edge==1) //Sprawdza czy jest echo
	{
		timer_value++;
		/* Sprawdza czy nie jest poza zasiegiem */
		if(timer_value > 91)
		{
			working = 0;
			rising_edge = 0;
			error = 1;
		}
	}
}
ISR (INT1_vect)
{
	if(working==1) //Sprawdza czy echo jest wysokie, włączanie timera
	{
		if(rising_edge==0)
		{
			rising_edge=1;
			TCNT0 = 0;
			timer_value = 0;
		}
		else //Sprawdza czy echo jest już niskie, wyłączenie timera
		{
			rising_edge = 0;
			distance_cm = (timer_value*256 + TCNT0)/58;
			working = 0;			
		}
	}
}

int main(void)
{
	/* Włączenie przerwań */
	Initialize_external_interrupt();
	Initialize_timer0();
    
    // inicjalizacja pinów
    DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD &=~ (1 << PIND3);
	DDRD |= (1 << PIND4);

    // zadana częstotiwość
    czestotliwosc = 22.5;

    // włączenie przerwań
	sei();

    // pętla główna
    while(1)
	{		
		Send_signal(); 
        if(distance_cm < 10){
            opoznienie = 1000 / (2 * 22.5);
            PORTB |= (1 << 7);
            PORTA |= (1 << 0);
            _delay_ms(opoznienie);
            PORTB &= ~(1 << 7);
            PORTA &=~(1<<0);
        }
    }
}

void Send_signal()
{
	if(working ==0) //Sprawdza czy pomiar zostal na pewno dokonany
	{
	_delay_ms(50);		//Restartuje czujnik
	PORTD &=~ (1 << PIND4);
	_delay_us(1);
	PORTD |= (1 << PIND4); //Wysyła 50 us sygnał by załączyć wysyłanie sygnału
	_delay_us(10);
	PORTD &=~ (1 << PIND4);
	working = 1;	// Sygnalizacja ze jest gotowy
	error = 0;		// żadnych błędów
	}	
}

void Initialize_external_interrupt()
{
	MCUCR |= (1 << ISC10); //Sprawdza logiczne zmiany stanów na INT1
	GICR |= (1 << INT1); //włącza INT1
}

void Initialize_timer0()
{
	TCCR0 |= (1 << CS00); //nie ma skalowania timera
	TCNT0 = 0;			//Reset timera
	TIMSK |= (1 << TOIE0); //włączenie przeładowania timera
}