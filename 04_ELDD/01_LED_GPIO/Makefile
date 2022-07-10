obj:= ioctl_led.o

KERNDIR = lib/modules/<uname -r>/build
PWD = $(shell pwd)
all:
	$(MAKE) -c $(KERNDIR) M=$(PWD) modules

clean:
	$(MAKE) -c $(KERNDIR) M=$(PWD) clean 