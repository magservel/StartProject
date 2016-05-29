

CFLAGS = -W -Wall #-ansi -pedantic
OFlAGS = -O

all: main

main: funcs.o main.o
	gcc -o main funcs.o main.o -Wall -lm -pg -std=c99

funcs.o: funcs.c
	gcc -o funcs.o -c funcs.c -Wall -lm -pg -std=c99

main.o: main.c funcs.h
	gcc -o main.o -c main.c -W -Wall -lm -pg -std=c99

clean:
	rm -rf *.o


