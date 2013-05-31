#
# Rogue Makefile 
# May 2013 - Bryant Moscon
#



rogue: main.o draw.o colors.o windows.o input.o rogue.o level.o
	gcc -ggdb3 -Wall -o rogue level.o input.o windows.o draw.o colors.o rogue.o main.o -lncursesw

level.o: level.c level.h
	gcc -ggdb3 -Wall -c -o level.o level.c

rogue.o : rogue.c rogue.h
	gcc -ggdb3 -Wall -c -o rogue.o rogue.c

input.o: input.c input.h
	gcc -ggdb3 -Wall -c -o input.o input.c

windows.o: windows.c windows.h
	gcc -ggdb3 -Wall -c -o windows.o windows.c

draw.o: draw.c draw.h
	gcc -ggdb3 -Wall -std=c99 -c -o draw.o draw.c

colors.o: colors.c colors.h
	gcc -ggdb3 -Wall -c -o colors.o colors.c

main.o: main.c
	gcc -ggdb3 -Wall -c -o main.o main.c

clean:
	rm rogue *.o
