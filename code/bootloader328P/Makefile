AVRDUDEFLAGS=-c usbtiny -pm328p


all: fuses install

fuses:
	avrdude ${AVRDUDEFLAGS} -U lock:w:0x2f:m
	avrdude ${AVRDUDEFLAGS} -U efuse:w:0x05:m
	avrdude ${AVRDUDEFLAGS} -U hfuse:w:0xd2:m
	avrdude ${AVRDUDEFLAGS} -U lfuse:w:0xf7:m
	
install:
	avrdude ${AVRDUDEFLAGS} -U flash:w:foodloader.hex:a
