#
# Rogue Makefile 
# May 2013 - Bryant Moscon
#


UNAME := $(shell uname -s)
CC = gcc
CCFLAGS = -Wall -Werror -pedantic -ggdb3 --std=c99
LINUX_LIBS = -lncursesw
OSX_LIBS = -lncurses

HEADERS = $(wildcard *.h)
SRC_FILES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SRC_FILES))

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