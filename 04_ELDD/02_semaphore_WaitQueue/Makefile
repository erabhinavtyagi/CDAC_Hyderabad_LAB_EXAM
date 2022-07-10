obj-m := driver.o

KERN_DIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	gcc -o write write.c
	gcc -o read  read.c

clean	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf read write