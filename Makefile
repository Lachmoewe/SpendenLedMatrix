AVRFLAGS = -D AVRMODE -std=c99 -mmcu=atmega8 -O0
GCFLAGS = -D SIMMODE -std=c99 `sdl-config --cflags --libs` -lpthread

all: program.elf sim/simulation 

program.elf: main.c gfx.c
	avr-gcc main.c gfx.c delay.c $(AVRFLAGS) -o program.elf
	avr-objcopy -j .text -O ihex program.elf program.hex 

sim/simulation: main.c sim/gfx.c
	gcc main.c sim/gfx.c sim/delay.c $(GCFLAGS) -o 'sim/simulation'

flash:
	avrdude -c usbasp -p atmega8 -U program.hex

clean:
	rm program.elf program.hex sim/simulation

test:
	avr-gcc test.c delay.c $(AVRFLAGS) -o test.elf
	avr-objcopy -j .text -O ihex test.elf test.hex

testflash:
	avrdude -c usbasp -p atmega8 -U test.hex

