#define _BSD_SOURCE  /* for usleep() */
#include <unistd.h>

void _udelay(int t) {
        usleep(t);
}
void _mdelay(int t) {
        usleep(t*1000);
}
void _delay(int t) {
        sleep(t);
}
