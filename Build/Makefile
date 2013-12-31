TEMPLATEROOT=..

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 
CLEANOTHER = libdriver.a

all: libdriver.a 

include $(TEMPLATEROOT)/Makefile.common

ELF=
STARTUP=

OBJS =  adc.o \
 aes.o \
 can.o \
 comp.o \
 cpu.o \
 crc.o \
 des.o \
 eeprom.o \
 emac.o \
 epi.o \
 flash.o \
 fpu.o \
 gpio.o \
 hibernate.o \
 i2c.o \
 interrupt.o \
 lcd.o \
 mpu.o \
 pwm.o \
 qei.o \
 shamd5.o \
 ssi.o \
 sw_crc.o \
 sysctl.o \
 sysexc.o \
 systick.o \
 timer.o \
 uart.o \
 udma.o \
 usb.o \
 watchdog.o 

libdriver.a: ${OBJS}
	$(AR) -cr libdriver.a ${OBJS}


