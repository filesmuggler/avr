#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define Red_diode PINA6
#define Green_diode PINA7
#define Button_pin PA5
#define Servo_pin PIND7

// global variable to count the number of overflows
volatile uint8_t tot_overflow;

// initialize timer, interrupt and variable
void timer0_init()
{
  // set up timer with prescaler = 256
  TCCR0 |= (1 << CS02);

  // initialize counter
  TCNT0 = 0;

  // enable overflow interrupt
  TIMSK |= (1 << TOIE0);

  // enable global interrupts
  sei();

  // initialize overflow counter variable
  tot_overflow = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
  // keep a track of number of overflows
  tot_overflow++;
}

int main(void)
{
  // connect led to pin PC0
  //DDRC |= (1 << 0);
  DDRA = 0b00000011;
  DDRD = 0xFF;

  // initialize timer
  timer0_init();

  // loop forever
  while (1)
  {
    if (PINA & (1<<Button_pin))
    {
      PORTA |= (1 << Green_diode); // toggles the led
      _delay_ms(100);
      PORTA &= ~(1 << Green_diode);
    }
    // check if no. of overflows = 12
    if (tot_overflow >= 100) // NOTE: '>=' is used
    {
      if (TCNT0 > 53)
      {
        PORTA |= (1 << Red_diode); // toggles the led
        _delay_ms(100);
        PORTA &= ~(1 << Red_diode);
        TCNT0 = 0;        // reset counter
        tot_overflow = 0; // reset overflow counter
      }
    }
  }
}