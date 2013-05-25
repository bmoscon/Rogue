#
# Rogue Makefile 
# May 2013 - Bryant Moscon
#



rogue: main.o draw.o colors.o windows.o
	gcc -ggdb3 -Wall -o rogue windows.o draw.o colors.o main.o -lncursesw

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
