AVRFLAGS = "-D AVR -std=c99 -mmcu=atmega8"
GCFLAGS = "-D SIM -std=c99 `sdl-config --cflags --libs`"

all: program.elf sim/simulation 

program.elf: main.c gfx.c
	echo "program.elf, program.hex"
	avr-gcc main.c gfx.c $(AVRFLAGS) -o program.elf
	avr-objcopy -j .text -O ihex program.elf program.hex 

sim/simulation: main.c sim/gfx.c
	echo "sim"
	gcc main.c sim/gfx.c $(GCFLAGS) -o 'sim/simulation'



