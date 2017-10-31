#!/bin/sh

autoscan # check new or updat4d files
aclocal # generate aclocal.m4
autoheader
autoconf # generate configure based on configure.ac
automake --add-missing # generate Makefile.in based on Makefile.am and aclocal.m4
mkdir -p ${D}{bindir}/prajna
 ./configure CC=aarch64-linux-gnu-gcc CXX=aarch64-linux-gnu-g++ --host=arm64 --prefix=${D}${bindir}/prajna
 #./configure CC=arm-linux-gnueabi-gcc CXX=arm-linux-gnueabi-g++ --host=arm --prefix=${D}${bindir}/prajna

