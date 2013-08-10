#include <avr/io.h>
#include "delay.h"
#define DATA PB4
#define SCK PB3
#define WRITEOUT PB2
void main(void) {
        DDRD = 0xff;
        DDRC = 0xff;
        DDRB = 0xff;
        PORTC |= (1<<PC0);
        uint8_t state = 0;
        while(1) {
                for (int i=0;i<12;i++) {
                                
                        PORTB &= (0<<DATA); //D
                        PORTB |= (1<<SCK); //SCK
                        PORTB &= (0<<SCK);
                        //state=!state;
                }
                PORTB |= (1<<WRITEOUT);
                PORTB &= (0<<WRITEOUT);
                _mdelay(10);
                for (int i=0;i<12;i++) {
                                
                        PORTB |= (1<<DATA); //D
                        PORTB |= (1<<SCK); //SCK
                        PORTB &= (0<<SCK);
                        //state=!state;
                }
                PORTB |= (1<<WRITEOUT);
                PORTB &= (0<<WRITEOUT);
                _mdelay(30);
        }


}
