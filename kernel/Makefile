
obj-m := prajna_k.o

export KBUILD=../tmp
export KROOT=~/Desktop/kernel/linux-3.12.17

all:modules

modules:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules

modules_install:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules_install

install:
	@echo Do nothing

kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) clean

distclean clean:kernel_clean
	rm -rf Module.symvers modules.order
