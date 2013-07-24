// awesome display code for SpendenBox-LedDisplay
// author: lachmoewe
// license: GPLv3
// c is best viewed with 8 space tab

#ifdef AVR
#include <avr/io.h>
#include "gfx.h"
#elif SIM
#include "sim/gfx.h"
#endif

#define true 1
#define false 0


void main(void) {
        setLedXY(5,5,1);
        while(true) {
                canvasUpdate();
        }


        // return 0;
}
