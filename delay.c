#include <util/delay_basic.h>
// delay_basic.h contains:
// void _delay_loop1(uint8_t)  with 256 possible iterations
// void _delay_loop2(uint16_t) with 65536 possible iterations


// this currently only works for 8MHz :D

void _udelay(int t) {  // do _NOT_ rely on this, it is not accurate at all
        for (uint8_t i=0; i<t; i++) {
                _delay_loop_1(2);
        }
}
void _mdelay(int t) {
        for (uint8_t i=0; i<t; i++) {
                _delay_loop_2(2000);
        }
        
}
void _delay(int t) {
        for (uint8_t i=0; i<t; i++) {
                for (uint8_t n=0; n<31; n++) {
                        _delay_loop_2(0);
                }
        }
}
