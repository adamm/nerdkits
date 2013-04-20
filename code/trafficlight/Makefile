GCCFLAGS=-g -Os -Wall -mmcu=atmega168 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-c avr109 -p m168 -b 115200 -P /dev/ttyUSB0
LINKOBJECTS=../libnerdkits/delay.o ../libnerdkits/lcd.o ../libnerdkits/uart.o

all:	trafficlight-upload

trafficlight.hex:	trafficlight.c
	make -C ../libnerdkits
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o trafficlight.o trafficlight.c ${LINKOBJECTS}
	avr-objcopy -j .text -O ihex trafficlight.o trafficlight.hex
	
trafficlight.ass:	trafficlight.hex
	avr-objdump -S -d trafficlight.o > trafficlight.ass
	
trafficlight-upload:	trafficlight.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:trafficlight.hex:a
