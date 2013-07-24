all: AVR LINUX

AVR:
	avr-gcc -D AVR -std=c99 -mmcu=atmega8 main.c -o program.elf

LINUX:
	gcc -D LINUX -std=c99 main.c -o 'sim/simulation'



