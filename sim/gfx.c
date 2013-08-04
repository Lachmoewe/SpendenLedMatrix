
#include <pthread.h>
#include <semaphore.h>

#include <SDL/SDL.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "gfx.h"
#define SIZEX 12
#define SIZEY 10
// totally stolen from a tutorial

static int keepRunning = 1;

void intHandler(int dummy) {
            keepRunning = 0;
}


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

SDL_Surface* screen = NULL;
void canvasInit() {
        signal(SIGINT, intHandler);

        /* Initialize the SDL library and the video subsystem */
        if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
                fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
                exit(1);
        }
        atexit(SDL_Quit);

        /*
         * Initialize the display in a 120x100 8-bit palettized mode,
         * requesting a software surface
         */
        screen = SDL_SetVideoMode(120, 100, 8, SDL_SWSURFACE|SDL_ANYFORMAT);
        if ( screen == NULL ) {
                fprintf(stderr, "Couldn't set 120x100x8 video mode: %s\n", SDL_GetError());
                exit(1);
        }
        pthread_t pth; // thread identifier
        pthread_create(&pth, NULL, canvasShow,"Updating screen...");
}

/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
        int bpp = surface->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to set */
        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        switch (bpp) {
                case 1:
                        *p = pixel;
                        break;

                case 2:
                        *(Uint16 *)p = pixel;
                        break;

                case 3:
                        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                                p[0] = (pixel >> 16) & 0xff;
                                p[1] = (pixel >> 8) & 0xff;
                                p[2] = pixel & 0xff;
                        }
                        else {
                                p[0] = pixel & 0xff;
                                p[1] = (pixel >> 8) & 0xff;
                                p[2] = (pixel >> 16) & 0xff;
                        }
                        break;

                case 4:
                        *(Uint32 *)p = pixel;
                        break;

                default:
                        break;           /* shouldn't happen, but avoids warnings */
        } // switch
}

// this will be threaded
void *canvasShow(void *arg) {
        /* Code to set a red pixel at the center of the screen */
        Uint32 color, red, black;
        red=SDL_MapRGB(screen->format,255,0,0);
        black=SDL_MapRGB(screen->format,0,0,0);

        while(keepRunning) {
                /* Lock the screen for direct access to the pixels */
                if ( SDL_MUSTLOCK(screen) ) {
                        if ( SDL_LockSurface(screen) < 0 ) {
                                fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
                        }
                }

                for (int y=0; y<SIZEY; y++){
                        for (int x=0; x<SIZEX; x++) {
                                if (matrix[x+y*12]) {
                                        color = red;
                                } else {
                                        color = black;
                                }
                                for(int h=0; h<10; h++) {
                                        for(int v=0; v<10; v++) {
                                                putpixel(screen, x*10+h, y*10+v, color);
                                        }
                                }
                        }
                }

                if ( SDL_MUSTLOCK(screen) ) {
                        SDL_UnlockSurface(screen);
                }
                /* Update just the part of the display that we've changed */
                SDL_UpdateRect(screen,0,0,0,0);
                usleep(50000);
        }
        return NULL;
}

void setLedXY(int x, int y, int value) { 
        // setLedXY from 0,0 to 9,11, value 0 or 1
        matrix[x+y*12]=value;
        if(!keepRunning) exit(0);
        //canvasShow();
}
int getLedXY(int x, int y) {
        return matrix[x+y*12];
}

