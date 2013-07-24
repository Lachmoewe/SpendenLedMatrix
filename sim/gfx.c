#ifndef GFX_H
#define GFX_H

#include "SDL.h"
#include "gfx.h"
// totally stolen from a tutorial

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

/* Initialize the SDL library and the video subsystem */
if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
}

/* Clean up on exit */
atexit(SDL_Quit);

/*
 * Initialize the display in a 240x200 8-bit palettized mode,
 * requesting a software surface
 */
screen = SDL_SetVideoMode(240, 200, 8, SDL_SWSURFACE|SDL_ANYFORMAT);
if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 240x200x8 video mode: %s\n", SDL_GetError());
        exit(1);
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
void canvasShow() {
        /* Code to set a red pixel at the center of the screen */
        Uint32 color;


        x = screen->w / 2;
        y = screen->h / 2;

        /* Lock the screen for direct access to the pixels */
        if ( SDL_MUSTLOCK(screen) ) {
                if ( SDL_LockSurface(screen) < 0 ) {
                        fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
                        return;
                }
        }

        for (int y=0; y<SIZEY; y++){
                for (int x=0; x<SIZEX; x++) {
                        if (value) {
                                color = red;
                        } else {
                                color = black;
                        }
                        putpixel(screen, x, y, color);
                        putpixel(screen, x+1, y, color);
                        putpixel(screen, x, y+1, color);
                        putpixel(screen, x+1, y+1, color);
                }
        }

        if ( SDL_MUSTLOCK(screen) ) {
                SDL_UnlockSurface(screen);
        }
        /* Update just the part of the display that we've changed */
        SDL_UpdateRect(screen, x, y, 2, 2);
}
void setLedXY(int x, int y, int value) { 
        // setLedXY from 0,0 to 9,11, value 0 or 1
        *(canvas+x+y*12)=value;
}
int getLedXY(int x, int y) {
        return *(canvas+x+y*12);
}

