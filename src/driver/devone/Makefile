
#CFLAGS += -Wall
#CFILES = devone.c

obj-m +:= devone.o
#sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) V=1 modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
