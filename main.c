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


unsigned char pics[2][8] = {
  { 0b11011011,
    0b10010010,
    0b10010010, 
    0b10010010,
    0b10010010,
    0b10010010,
    0b10010010,
    0b11011011 },
  { 0b10000001,
    0b01000010,
    0b01111110, 
    0b01011010,
    0b01111110,
    0b01111110,
    0b01100110,
    0b00111100 },
};

void main(void) {
  canvasInit();
  int pic=0;
  while(true) {
    for(int y = 0; y < 10; y++)
      for(int x = 0; x < 12; x++) {
        // 5ms delay (see delay.h for reference)
        _mdelay(5);

        int color = 0;
        if (y >= 1 && y < 9 &&
            x >= 2 && x < 10)
          color = (pics[pic][y - 1] >> (9 - x)) & 1;
        setLedXY(x, y, color);
      }

    pic = (pic + 1) % 2;
  }
}
