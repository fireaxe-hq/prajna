
default:
	make -C kernel
	make -C paramita
	make -C skandhas

clean:
	make -C kernel clean
	make -C paramita clean
	make -C skandhas clean

