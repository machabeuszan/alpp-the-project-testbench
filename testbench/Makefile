##########################################################################################
# Name: Makefile
# Project: alpp
# Author: Adrian Ciesielski
# Creation Date: 2012-08-31
# Copyright: (c) 2012 by Adrian Ciesielski
# License: GNU LGPL v3 (see COPYING)
# Version: 0.0.1
##########################################################################################

# Configuration

# uC parameters
DEVICE	= atmega8
F_CPU	= 16000000


# paths definitions
AVR_PATH	= /usr/local/avr

AVR_INCLUDE	= $(AVR_PATH)/include
AVR_LIBS	= $(AVR_PATH)/lib


# internal configuration - DO NOT modify anything beyond this point
SRCPREFIX = src
OBJS	  = obj
ALPPDIR   = ../release



# compile flags
FLAGSCOMMON = -I. -Wall  -I$(ALPPDIR)/include  -I$(AVR_INCLUDE) -g
CFLAGS	 = $(FLAGSCOMMON) --std=c99
CXXFLAGS = $(FLAGSCOMMON)

LDFLAGS	 = -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) -I. -Wall -g 

# list of object to build
OBJECTS	 = $(addprefix $(SRCPREFIX)/, main.o )

# command to compile .c objects
COMPILEC = avr-gcc  -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) $(CFLAGS) 
# command to compile .cpp objects
COMPILE	 = avr-g++ -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) $(CXXFLAGS) 

LINK	 = avr-g++ -Os	 -DF_CPU=$(F_CPU) -DF_CPU=$(F_CPU)  $(LDFLAGS) 


all: main.elf	
	avr-size $< -C --mcu=$(DEVICE)

help:
	@echo "Jak używać:"
	@echo "make simul .... aby zbudować i zasymulować testy"
	@echo "make hex ...... aby zbuodować plik wsadowy do uC"
	@echo "make main.elf . aby zbudować sam program"
	@echo "make clean .... aby wyczyścić"

clean:
	rm -fR *.o *.elf *.hex $(OBJECTS)
	

hex:main.hex

simul:main.elf
	simulavr -d $(DEVICE) -f $< -W 0x20,- -R 0x22,- -T exit
	

%.o: %.cpp 
	$(COMPILE) -c $< -o $@

.o.c:
	$(COMPILEC) -c $< -o $@
	
.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
	
.c.s:
	$(COMPILE) -S $< -o $@


	
main.elf: $(OBJECTS)
	avr-g++  $(LDFLAGS) -o $@ $^  -L../release -lalpp
	#$(LINK) -o $@ $^
	
main.hex: main.elf
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size $< -C --mcu=$(DEVICE)
	

