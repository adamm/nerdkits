GCCFLAGS=-g -Os -Wall -mmcu=atmega168 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-c avr109 -p m168 -b 115200 -P /dev/ttyUSB0
LINKOBJECTS=../libnerdkits/delay.o ../libnerdkits/lcd.o ../libnerdkits/uart.o

all:	tempsensor-upload

tempsensor.hex:	tempsensor.c
	make -C ../libnerdkits
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o tempsensor.o tempsensor.c ${LINKOBJECTS}
	avr-objcopy -j .text -O ihex tempsensor.o tempsensor.hex
	
tempsensor.ass:	tempsensor.hex
	avr-objdump -S -d tempsensor.o > tempsensor.ass
	
tempsensor-upload:	tempsensor.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:tempsensor.hex:a
