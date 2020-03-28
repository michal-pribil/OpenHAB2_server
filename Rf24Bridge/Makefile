#############################################################################
#
# Makefile for librf24 examples on Linux
#
# License: GPL (General Public License)
# Author:  gnulnulf <arco@appeltaart.mine.nu>
# Date:    2013/02/07 (version 1.0)
#
# Description:
# ------------
# use make all and make install to install the examples
#

#ifeq ($(wildcard ../Makefile.inc), )
#	$(error Configuration not found. Run ./configure first)
#endif

#include ../Makefile.inc

OS=LINUX
SOC=BCM2835
DRIVER=RPi
CPUFLAGS=-marm -march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard
CFLAGS=-marm -march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -O0 -Wall -pthread -g
PREFIX=/usr/local
REMOTE_PREFIX=/usr/local
LIB=rf24
LIBNAME=librf24.so.1.3.4
LIB_VERSION=1.3.4
LIBSYMLINKS=librf24.so.1.3 librf24.so.1 librf24.so
LIBDEPRECATE=librf24-bcm.so
CC=arm-linux-gnueabihf-gcc
CXX=arm-linux-gnueabihf-g++
LIB_DIR=/usr/local/lib
REMOTE_LIB_DIR=/usr/local/lib
HEADER_DIR=/usr/local/include/RF24
REMOTE_HEADER_DIR=/usr/local/include/RF24
DRIVER_DIR=utility/RPi
ARCH_DIR=utility
SHARED_LINKER_FLAGS= -shared -Wl,-soname,librf24.so.1
SHARED_LINKER_LIBS= -pthread
LDCONFIG=ldconfig
REMOTE_LDCONFIG=/sbin/ldconfig
EXAMPLES_DIR=/usr/local/bin
REMOTE_EXAMPLES_DIR=/usr/local/bin

# define all programs
PROGRAMS = Rf24Bridge

BINARY_PREFIX = rf24
SOURCES = $(PROGRAMS:=.cpp)

LIBS=-l$(LIB)
ifeq ($(DRIVER), LittleWire)
	LIBS+= -llittlewire-spi
endif

all: $(PROGRAMS)

$(PROGRAMS): $(SOURCES)
	$(CXX) $(CFLAGS) -I$(HEADER_DIR)/.. -I.. -L$(LIB_DIR) $@.cpp $(LIBS) -o $@

clean:
	@echo "[Cleaning]"
	rm -rf $(PROGRAMS)

#install: all
#        @echo "[Installing examples to $(EXAMPLES_DIR)]"
#        @mkdir -p $(EXAMPLES_DIR)
#        @for prog in $(PROGRAMS); do \
#                install -m 0755 $${prog} $(EXAMPLES_DIR)/$(BINARY_PREFIX)-$${prog}; \
#        done

#upload: all
#        @echo "[Uploading examples to $(REMOTE):$(REMOTE_EXAMPLES_DIR)]"
#ifeq ($(REMOTE),)
#        @echo "[ERROR] Remote machine not configured. Run configure with respective arguments."
#        @exit 1
#endif
#        @ssh -q -t -p $(REMOTE_PORT) $(REMOTE) "mkdir -p $(REMOTE_EXAMPLES_DIR)"
#        @ssh -q -t -p $(REMOTE_PORT) $(REMOTE) "mkdir -p /tmp/RF24_examples"
#        @scp -q -P $(REMOTE_PORT) $(PROGRAMS) $(REMOTE):/tmp/RF24_examples
#        @for prog in $(PROGRAMS); do \
#                ssh -q -t -p $(REMOTE_PORT) $(REMOTE) "sudo install -m 0755 /tmp/RF24_examples/$${prog} $(REMOTE_EXAMPLES_DIR)/$(BINARY_PREFIX)-$${prog}"; \
#        done
#        @ssh -q -t -p $(REMOTE_PORT) $(REMOTE) "rm -rf /tmp/RF24_examples"
#
#.PHONY: install upload


#include Makefile.examples
