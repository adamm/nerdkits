GCCFLAGS=-g -Os -Wall -mmcu=atmega168 
LINKFLAGS=-Wl,-u,vfprintf -lprintf_flt -Wl,-u,vfscanf -lscanf_flt -lm
AVRDUDEFLAGS=-c avr109 -p m168 -b 115200 -P /dev/ttyUSB0
LINKOBJECTS=../libnerdkits/delay.o ../libnerdkits/lcd.o ../libnerdkits/uart.o

all:	led_blink-upload

led_blink.hex:	led_blink.c
	make -C ../libnerdkits
	avr-gcc ${GCCFLAGS} ${LINKFLAGS} -o led_blink.o led_blink.c ${LINKOBJECTS}
	avr-objcopy -j .text -O ihex led_blink.o led_blink.hex
	
led_blink.ass:	led_blink.hex
	avr-objdump -S -d led_blink.o > led_blink.ass
	
led_blink-upload:	led_blink.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:led_blink.hex:a
