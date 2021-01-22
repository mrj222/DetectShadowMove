obj-m += pnet.o
default:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean
clean:
	-rm *.mod.* *.ko *.o *.order *.symvers