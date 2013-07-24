#include <avr/io.h>
#include "gfx.h"

#define true 1
#define false 0

#define SIZEX 12
#define SIZEY 10

int matrix[120] = {
        0,0,0,0,0,0,0,0,0,0,0,0,
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
        DDRB = 0xff;
}

void canvasRowHigh(int row) {
        switch (row) {
                case 0: PORTC = (1<<PC0); break;
                case 1: PORTC = (1<<PC1); break;
                case 2: PORTC = (1<<PC2); break;
                case 3: PORTC = (1<<PC3); break;
                case 4: PORTD = (1<<PD4); break;
                case 5: PORTD = (1<<PD5); break;
                case 6: PORTD = (1<<PD6); break;
                case 7: PORTD = (1<<PD7); break;
                case 8: PORTB = (1<<PB0); break;
                case 9: PORTB = (1<<PB1); break;
        }
}
void canvasRowLow(int row) {
        switch (row) {
                case 0: PORTC = (0<<PC0); break;
                case 1: PORTC = (0<<PC1); break;
                case 2: PORTC = (0<<PC2); break;
                case 3: PORTC = (0<<PC3); break;
                case 4: PORTD = (0<<PD4); break;
                case 5: PORTD = (0<<PD5); break;
                case 6: PORTD = (0<<PD6); break;
                case 7: PORTD = (0<<PD7); break;
                case 8: PORTB = (0<<PB0); break;
                case 9: PORTB = (0<<PB1); break;
        }
}
void canvasRowPump(int value) {
       PORTB = (value<<PB4); 
       PORTB = (1<<PB3);
       PORTB = (0<<PB3); 
}

void setLedXY(int x, int y, int value) { 
        // setLedXY from 0,0 to 9,11, value 0 or 1
        *(canvas+x+y*12)=value;
}
int getLedXY(int x, int y) {
        return *(canvas+x+y*12);
}

void canvasShow() { 
        // this shit needs to execute really fast
        for (int y=0; y<SIZEY; y++){
                canvasRowHigh(y);
                for (int x=0; x<SIZEX; x++) {
                        canvasRowPump(!(getLedXY(x,y)));
                }
                // sleep(shortamountoftime);
                canvasRowLow(y);
        }
}
