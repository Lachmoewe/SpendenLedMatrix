// awesome display code for SpendenBox-LedDisplay
// author: lachmoewe
// license: GPLv3
// c is best viewed with 8 space tab

#ifdef AVR
//#include <avr/io.h>
#include "gfx.h"
void usleep(int t) {}
#elif SIM
#include "sim/gfx.h"
#include <unistd.h>
#endif

#define true 1
#define false 0


void main(void) {
        canvasInit();
        int x=0;
        int color=1;
        while(true) {
                canvasShow();
                usleep(5000);
                setLedXY(x,0,color);

                x++;
                if (x > 119) {
                        x=0;
                        color=!color;
                }
        }
}
