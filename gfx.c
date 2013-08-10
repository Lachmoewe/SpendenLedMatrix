

#include "gfx.h"
#include "delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define true 1
#define false 0

#define SIZEX 12
#define SIZEY 10

int matrix[120] = {
        1,0,1,0,1,0,1,0,1,0,1,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0};

int *canvas = matrix;

void canvasInit(void) {
        DDRC = 0b00001111;
        DDRD = 0b11110000;
        DDRB = 0b00011111;
        //TCCR2 = (1<<CS21);;
        //TIMSK |= (1<<TOIE0);

        TCCR0 |= _BV(CS01);
        TIMSK |= _BV(TOIE0);
        TIFR  |= _BV(TOV0);
//        sei();
}

void canvasRowHigh(int row) {
        switch (row) {
                case 0: PORTC |= (1<<PC0); break;
                case 1: PORTC |= (1<<PC1); break;
                case 2: PORTC |= (1<<PC2); break;
                case 3: PORTC |= (1<<PC3); break;
                case 4: PORTD |= (1<<PD4); break;
                case 5: PORTD |= (1<<PD5); break;
                case 6: PORTD |= (1<<PD6); break;
                case 7: PORTD |= (1<<PD7); break;
                case 8: PORTB |= (1<<PB0); break;
                case 9: PORTB |= (1<<PB1); break;
        }
}
void canvasRowLow(void) {
        PORTC &= ~( (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3) );
        PORTD &= ~( (1<<PD4) | (1<<PD5) | (1<<PD6) | (1<<PD7) );
        PORTB &= ~( (1<<PB0) | (1<<PB1) );
}

void setLedXY(int x, int y, int value) { 
        // setLedXY from 0,0 to 9,11, value 0 or 1
        matrix[x+y*12]=value;
}
int getLedXY(int x, int y) {
        return matrix[x+y*12];
}
void canvasShow() { 
        // this shit needs to execute really fast
        for (int y=0; y<SIZEY; y++){
                canvasRowHigh(y);
                for (int x=0; x<SIZEX; x++) {
                        // PB4 = current Led value
                        if (!getLedXY(x,y)) {
                                PORTB &= ~(1<<PB4);
                        } else {
                                PORTB |= (1<<PB4);
                        }

                        // set clk high
                        PORTB |= (1<<PB3);
                        _udelay(1);
                        // set clk low
                        PORTB &= ~(1<<PB3);
                }
                // writeout registers
                PORTB |= (1<<PB2);
                _udelay(1);
                PORTB &= ~(1<<PB2);
                canvasRowLow();
                _udelay(10);
        }
}
ISR (SIG_OVERFLOW0 /*TIMER2_OVF_vect*/) {
        cli();
        canvasShow();
        sei();
}
