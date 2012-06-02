ifneq ($(KERNELRELEASE),)
#build by DKMS or included in a kernel tree

obj-m += gwe_rs232.o

else
#manual build out of tree

KDIR := /lib/modules/3.1.9+/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif