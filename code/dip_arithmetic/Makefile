GCCFLAGS=-g -Os -Wall -mmcu=atmega168 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-c avr109 -p m168 -b 115200 -P /dev/ttyUSB0
LINKOBJECTS=../libnerdkits/delay.o ../libnerdkits/lcd.o ../libnerdkits/uart.o

all:	dip_arithmetic-upload

dip_arithmetic.hex:	dip_arithmetic.c
	make -C ../libnerdkits
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o dip_arithmetic.o dip_arithmetic.c ${LINKOBJECTS}
	avr-objcopy -j .text -O ihex dip_arithmetic.o dip_arithmetic.hex
	
dip_arithmetic.ass:	dip_arithmetic.hex
	avr-objdump -S -d dip_arithmetic.o > dip_arithmetic.ass
	
dip_arithmetic-upload:	dip_arithmetic.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:dip_arithmetic.hex:a
