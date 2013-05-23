

rogue: main.o draw.o colors.o
	gcc -ggdb3 -Wall -o rogue draw.o colors.o main.o -lncursesw

draw.o: draw.c
	gcc -ggdb3 -Wall -std=c99 -c -o draw.o draw.c

colors.o: colors.c
	gcc -ggdb3 -Wall -c -o colors.o colors.c

main.o: main.c
	gcc -ggdb3 -Wall -c -o main.o main.c


clean:
	rm rogue *.o
