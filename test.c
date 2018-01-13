
#include <avr/io.h>
#include <util/delay.h>
void sleep(uint8_t millisec){
    while(millisec){
        _delay_ms(1);
        millisec--;
    }
}

int main(){
    DDRC |=1<<PB7;
    while(1){
        PORTC &= ~(1<<PB7);
        sleep(100);

        PORTC !=(1<<PB7);
        sleep(100);
    }
    return 0;
}