#!/bin/sh

autoscan # check new or updat4d files
aclocal # generate aclocal.m4
autoheader
autoconf # generate configure based on configure.ac
automake --add-missing # generate Makefile.in based on Makefile.am and aclocal.m4
# ./configure CC=arm-linux-gnueabi-gcc CXX=arm-linux-gnueabi-g++ --host=arm --prefix=/home/hao/Desktop/arm/qemu_img
# ./configure --prefix=/home/hao/Desktop/arm/qemu_img

