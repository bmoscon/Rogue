# test tool for rooms algorithm
# 
# Bryant Moscon - July 2013
#


UNAME := $(shell uname -s)
CC = gcc
CCFLAGS = -Wall -Werror -pedantic -ggdb3 --std=c99
LINUX_LIBS = -lncursesw
OSX_LIBS = -lncurses

HEADERS = $(wildcard *.h)
SRC_FILES = $(wildcard *.c)
OBJECTS = $(subst .c,.o,$(SRC_FILES))

BIN = rooms

all: $(BIN)

clean: 
	rm -f $(OBJECTS) $(BIN)

$(BIN): $(OBJECTS)
ifeq ($(UNAME),Darwin)
	$(CC) -o $(BIN) $(OBJECTS) $(OSX_LIBS)
else ifeq ($(UNAME),Linux)
	$(CC) -o $(BIN) $(OBJECTS) $(LINUX_LIBS)
endif    


%.o: %.c $(HEADERS) Makefile
	$(CC) $(CCFLAGS) -c $< -o $@