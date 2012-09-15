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

OBJSNAMES = main
# definitions of paths

#where your avr is kept
AVR_PATH =/usr/local/avr

# precise subdirectories if needed
AVR_INCLUDE	= $(AVR_PATH)/include
AVR_LIBS	= $(AVR_PATH)/lib


# where are soruces files
SRCPREFIX = src
#OBJS	  = obj
# directory where is release version of the ALPP library
ALPPDIR   = ../release



#common flags for LD, CC and CXX
FLAGS	 = -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE) -I. -Wall -g

# compile flags
CFLAGS	 = -I$(ALPPDIR)/include  -I$(AVR_INCLUDE) --std=c99

CXXFLAGS = -I$(ALPPDIR)/include  -I$(AVR_INCLUDE)

#link flags
LDFLAGS	 = -L../release -lalpp




PREOBJS 	= $(addsuffix .o , $(OBJSNAMES))

# list of object to build
OBJECTS	 = $(addprefix $(SRCPREFIX)/, $(PREOBJS) )


CC	= avr-gcc
CXX	= avr-g++
LD	= avr-g++


all: main.elf
	avr-size $< -C --mcu=$(DEVICE)

help:
	@echo "Jak używać:"
	@echo "make simul .... aby zbudować i zasymulować testy"
	@echo "make hex ...... aby zbuodować plik wsadowy do uC"
	@echo "make elf ...... aby zbudować sam program"
	@echo "make clean .... aby wyczyścić"

clean:
	rm -fR *.o *.elf *.hex $(OBJECTS)

elf:main.elf

hex:main.hex

simul:main.elf
	@printf "\n\n"
	simulavr -d $(DEVICE) -f $< -W 0x20,- -R 0x22,- -T exit
	@printf "\n"


%.o: %.cpp
	$(CXX) $(FLAGS) $(CXXFLAGS) -c $< -o $@

.o.c:
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

.S.o:
	$(CXX) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(CXX) -S $< -o $@



main.elf: $(OBJECTS)
	$(LD)  -o $@ $^ $(FLAGS) $(LDFLAGS)

main.hex: main.elf
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size $< -C --mcu=$(DEVICE)


