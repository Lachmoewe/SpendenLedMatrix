SRC = main.c gfx.c
HEADERS = gfx.h
OBJECTS = $(SRC:.c=.o)
AVRFLAGS = -D AVR -std=c99 -mmcu=atmega8

SIMSRC = main.c sim/gfx.c
SIMHEADERS = sim/gfx.h
SIMOBJECTS = $(SIMSRC:.c=.o)
GCFLAGS = -D SIM -std=c99

all: program.elf sim/simulation 

program.elf: main.c gfx.c
	avr-gcc main.c gfx.c $(AVRFLAGS) -o program.elf
	avr-objcopy -j .text -O ihex program.elf program.hex 

sim/simulation: main.c sim/gfx.c
	gcc main.c sim/gfx.c -D SIM -std=c99 `sdl-config --cflags --libs` -o 'sim/simulation'
clean:
	rm program.elf program.hex sim/simulation


