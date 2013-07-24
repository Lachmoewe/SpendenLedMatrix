SRC = main.c gfx.c
HEADERS = gfx.h
OBJECTS = $(SRC:.c=.o)
AVRFLAGS = -D AVR -std=c99 -mmcu=atmega8

SIMSRC = main.c sim/gfx.c
SIMHEADERS = sim/gfx.h
SIMOBJECTS = $(SIMSRC:.c=.o)
GCFLAGS = -D SIM -std=99

all: program.elf sim/simulation 

program.elf: $(OBJECTS)
	avr-gcc $(OBJECTS) $(AVRFLAGS) -o program.elf

sim/simulation: $(SIMOBJECTS)
	gcc $(SIMOBJECTS) $(GCFLAGS) `sdl-config --cflags --libs` -o 'sim/simulation'



