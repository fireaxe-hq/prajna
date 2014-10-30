#!/bin/sh

aclocal # generate aclocal.m4
autoheader
autoconf # generate configure based on configure.ac
automake --add-missing # generate Makefile.in based on Makefile.am and aclocal.m4
# ./configure CC=arm-qhao-linux-gnueabi-gcc --host=arm --prefix=/home/hao1404/Desktop/kernel/obj/prajna

