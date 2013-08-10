#include <avr/io.h>
#include "delay.h"
#define DATA PB4
#define SCK PB3
#define WRITEOUT PB2
void main(void) {
        DDRD = 0xff;
        DDRC = 0xff;
        DDRB = 0xff;
        PORTB |= (1<<PB0);
        while(1) {
                PORTB &= ~(1<<DATA); //D
                for (int i=0;i<12;i++) {                

                        PORTB |= (1<<SCK); //SCK
                        _udelay(1);          //          _____
                        PORTB &= ~(1<<SCK);  //   ______|     |_______
                }
                PORTB |= (1<<WRITEOUT);
                _udelay(1);
                PORTB &= ~(1<<WRITEOUT);
                _mdelay(50);

                PORTB |= (1<<DATA); //D
                for (int i=0;i<12;i++) {

                        PORTB |= (1<<SCK); //SCK
                        _udelay(1);
                        PORTB &= ~(1<<SCK);
                }
                PORTB |= (1<<WRITEOUT);
                _udelay(1);
                PORTB &= ~(1<<WRITEOUT);
                _mdelay(50);
        }
}
//Hallo du
