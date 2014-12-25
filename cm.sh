#!/bin/sh

autoscan # check new or updat4d files
aclocal # generate aclocal.m4
autoheader
autoconf # generate configure based on configure.ac
automake --add-missing # generate Makefile.in based on Makefile.am and aclocal.m4
# ./configure CC=arm-qhao-linux-gnueabi-gcc CXX=arm-qhao-linux-gnueabi-g++ --host=arm --prefix=/home/hao-64/Desktop/arm/qemu_img
# ./configure --prefix=/home/hao-64/Desktop/arm/qemu_img

