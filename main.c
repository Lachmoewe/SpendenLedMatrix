// awesome display code for SpendenBox-LedDisplay
// author: lachmoewe
// license: GPLv3
// c is best viewed with 8 space tab

// for the real thing
#ifdef AVR

#define F_CPU 8000000UL
#include "gfx.h"
#include <util/delay.h>

// for the simulation
#elif SIM

#include "sim/gfx.h"
#include <unistd.h>
void _delay_ms(double t) {
        int u=t*1000;
        usleep(u);
}
void _delay_us(double t) {
        int u=t;
        usleep(u);
}
#endif

#define true 1
#define false 0


void main(void) {
        canvasInit();
        int x=0;
        int color=1;
        while(true) {
                canvasShow();
                _delay_ms(50);
                setLedXY(x,0,color);

                x++;
                if (x > 119) {
                        x=0;
                        color=!color;
                }
        }
}
