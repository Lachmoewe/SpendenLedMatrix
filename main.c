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


#define SIZEX 12
#define SIZEY 10

#define PIC_W 64
#define PIC_H 32
/*unsigned char pics[PIC_H][PIC_W / 8] = {
        0b11101110,  0b11100000,  0b00000000,  0b00000000,  0b00010000,  0b00000000,  0b00000001,  0b00000100,
        0b10001000,  0b10000000,  0b00000000,  0b00000000,  0b00010000,  0b00000000,  0b00000000,  0b10001000,
        0b10001000,  0b10000000,  0b00000000,  0b00000000,  0b00010000,  0b00000000,  0b00000001,  0b11111100,
        0b11101110,  0b11100000,  0b00000000,  0b00000000,  0b01111100,  0b00000000,  0b00000011,  0b01110110,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00111000,  0b00000000,  0b00000111,  0b11111111,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00010000,  0b00000000,  0b00000101,  0b11111101,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000101,  0b00000101,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b11011000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b10000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b10000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b10000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11000000,  0b00000000,  0b00000000,  0b00001100,  0b11001100,  0b11000001,  0b10110011,  0b00000000,
        0b10000000,  0b00000000,  0b00000000,  0b00011001,  0b10011001,  0b10000011,  0b00011001,  0b10000000,
        0b11000000,  0b00000000,  0b00000000,  0b00110011,  0b00110011,  0b00000110,  0b00001100,  0b11000000,
        0b10000000,  0b00000000,  0b00000000,  0b00011001,  0b10011001,  0b10001100,  0b00011001,  0b10000000,
        0b11000000,  0b00000000,  0b00000000,  0b00001100,  0b11001100,  0b11011000,  0b00110011,  0b00000000,
        0b10000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,  0b00000000,
        0b11100100,  0b00011100,  0b01110001,  0b10010001,  0b00110011,  0b10111101,  0b00000000,  0b01111100,
        0b10010100,  0b00100000,  0b01001010,  0b01011001,  0b01001001,  0b00100001,  0b00000000,  0b00000100,
        0b11100100,  0b00011000,  0b01001010,  0b01010101,  0b01111001,  0b00111001,  0b00000000,  0b00011111,
        0b10000100,  0b00000100,  0b01001010,  0b01010011,  0b01001001,  0b00100000,  0b00000000,  0b00001110,
        0b10000111,  0b10111000,  0b01110001,  0b10010001,  0b01001001,  0b00111101,  0b00000000,  0b00000100,
};*/

void main(void) {
        canvasInit();
        while(true) {
                setLedXY(5,5,1);
                setLedXY(6,8,0);
                _mdelay(100);
                setLedXY(5,5,0);
                setLedXY(6,8,1);
                _mdelay(100);
        }
  //    int pic_x = 0, pic_y = PIC_H - SIZEY;
  //    int dir = 2;  /* 0: N, 1: NE, 2: E, 3: SE, 4: S, 5: SW, 6: W, 7: NW */
  //    while(true) {
  //            /* printf("dir=%i\tpic_x=%i\tpic_y=%i\n", dir, pic_x, pic_y); */
  //            /* Paint */
  //            for(int y = 0; y < 10; y++)
  //                    for(int x = 0; x < 12; x++) {
  //                            int px = pic_x + x, py = pic_y + y;
  //                            setLedXY(x, y, (pics[py][px / 8] >> (7 - (px % 8))) & 1);
  //                    }

  //            /* Y motion */
  //            switch(dir) {
  //                    case 0:
  //                    case 1:
  //                    case 7:
  //                            if (pic_y > 0)
  //                                    pic_y--;
  //                            else
  //                                    dir = rand() & 7;
  //                            break;
  //                    case 3:
  //                    case 4:
  //                    case 5:
  //                            if (pic_y < PIC_H - SIZEY)
  //                                    pic_y++;
  //                            else
  //                                    dir = rand() & 7;
  //                            break;
  //            }
  //            /* X motion */
  //            switch(dir) {
  //                    case 5:
  //                    case 6:
  //                    case 7:
  //                            if (pic_x > 0)
  //                                    pic_x--;
  //                            else
  //                                    dir = rand() & 7;
  //                            break;
  //                    case 1:
  //                    case 2:
  //                    case 3:
  //                            if (pic_x < PIC_W - SIZEX)
  //                                    pic_x++;
  //                            else
  //                                    dir = rand() & 7;
  //                            break;
  //            }
  //             _mdelay(50);
  //    }
}
