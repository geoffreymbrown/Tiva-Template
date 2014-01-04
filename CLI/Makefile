TEMPLATEROOT = ..

# compilation flags for gdb

INCLUDES = -I$(LIBROOT)/utils
CFLAGS  = -O1 -g -DUART_BUFFERED
ASFLAGS = -g 

# object files

OBJS=  main.o uartstdio.o ustdlib.o cmdline.o

# include common make file

include $(TEMPLATEROOT)/Makefile.common
vpath %.c $(LIBROOT)/utils

