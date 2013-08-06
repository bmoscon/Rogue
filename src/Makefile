#
# Rogue Makefile 
# May 2013 - Bryant Moscon
#


UNAME := $(shell uname -s)
CC = gcc
CCFLAGS = -Wall -Werror -pedantic -ggdb3 --std=c99
LINUX_LIBS = -lncursesw
OSX_LIBS = -lncurses

HEADERS = chars.h colors.h draw.h input.h items.h level.h logger.h rogue.h windows.h
OBJECTS = colors.o draw.o input.o items.o level.o logger.o main.o rogue.o windows.o

all: rogue

clean: 
	rm -f $(OBJECTS) rogue

rogue: $(OBJECTS)
ifeq ($(UNAME),Darwin)
	$(CC) -o rogue $(OBJECTS) $(OSX_LIBS)
else ifeq ($(UNAME),Linux)
	$(CC) -o rogue $(OBJECTS) $(LINUX_LIBS)
endif    


%.o: %.c $(HEADERS) Makefile
	$(CC) $(CCFLAGS) -c $< -o $@