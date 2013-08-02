// awesome display code for SpendenBox-LedDisplay
// author: lachmoewe
// license: GPLv3
// c is best viewed with 8 space tab

// for the real thing
#ifdef AVRMODE

#define F_CPU 8000000UL
#include "gfx.h"
#include "delay.h"



// for the simulation
#elif SIMMODE

#include "sim/gfx.h"
#include "sim/delay.h"
#endif

#define true 1
#define false 0


void main(void) {
        canvasInit();
        int x=0;
        int color=1;
        while(true) {
                _udelay(5000);
                setLedXY(x,0,color);

                x++;
                if (x > 119) {
                        x=0;
                        color=!color;
                }
        }
}
