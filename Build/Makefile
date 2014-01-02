TEMPLATEROOT=..

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 
CLEANOTHER = libdriver.a libusb.a

all: libdriver.a libusb.a

ELF=

include $(TEMPLATEROOT)/Makefile.common


vpath %.c $(LIBROOT)/driverlib
vpath %.c $(LIBROOT)/usblib
vpath %.c $(LIBROOT)/usblib/device
vpath %.c $(LIBROOT)/usblib/host


DriverOBJS =  adc.o \
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

USBOBJS = usbbuffer.o \
 usbdaudio.o \
 usbdbulk.o \
 usbdcdc.o \
 usbdcdesc.o \
 usbdcomp.o \
 usbdconfig.o \
 usbddfu-rt.o \
 usbdenum.o\
 usbdesc.o \
 usbdhandler.o \
 usbdhid.o \
 usbdhidkeyb.o \
 usbdhidmouse.o \
 usbdma.o \
 usbdmsc.o \
 usbhaudio.o \
 usbhhid.o \
 usbhhidkeyboard.o \
 usbhhidmouse.o \
 usbhhub.o \
 usbhmsc.o \
 usbhostenum.o \
 usbhscsi.o \
 usbkeyboardmap.o \
 usbmode.o \
 usbringbuf.o \
 usbtick.o \
 usbulpi.o


OBJS=$(DriverOBJS) $(USBOBJS)

libdriver.a: ${DriverOBJS}
	$(AR) -cr libdriver.a ${DriverOBJS}

libusb.a: ${USBOBJS}
	$(AR) -cr libusb.a ${USBOBJS}


