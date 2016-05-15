
obj-m := prajna_k.o

export KBUILD=../tmp
#QEMU_BASE=/home/haoqiang/Desktop/arm
QEMU_BASE=/home/qemu
#export KROOT=~/Desktop/kernel/linux-4.2
export KROOT=/home/vlx/linux-4.2

all:modules

modules:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules

modules_install:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules_install

install:
	cp -f *.ko $(QEMU_BASE)/zynq_qemu/
dist:
	@echo do nothin now

kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) clean

distclean clean:kernel_clean
	rm -rf Module.symvers modules.order
