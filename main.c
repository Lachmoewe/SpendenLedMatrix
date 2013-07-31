// awesome display code for SpendenBox-LedDisplay
// author: lachmoewe
// license: GPLv3
// c is best viewed with 8 space tab

#ifdef AVR
//#include <avr/io.h>
#include "gfx.h"
#elif SIM
#include "sim/gfx.h"
#endif

#define true 1
#define false 0


void main(void) {
        canvasInit();
        int x=0;
        int y=0;
        while(true) {
                canvasShow();
                setLedXY(x,y,1);

                x++;
                /*if (x>9) {
                        x=0;
                        y++;
                }*/
        }


        // return 0;
}
