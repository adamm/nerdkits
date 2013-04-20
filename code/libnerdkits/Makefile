GCCFLAGS=-g -Os -Wall -mmcu=atmega168 

all: delay.o lcd.o uart.o

delay.o: delay.c
	avr-gcc ${GCCFLAGS} -o delay.o -c delay.c

lcd.o: lcd.c
	avr-gcc ${GCCFLAGS} -o lcd.o -c lcd.c

uart.o: uart.c
	avr-gcc ${GCCFLAGS} -o uart.o -c uart.c
