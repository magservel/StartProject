

CFLAGS = -W -Wall #-ansi -pedantic
OFlAGS = -O

all: main

main: main.o funcs.o
#	gcc -o main main.o funcs.o 

funcs.o: funcs.c
	gcc -o funcs.o -c funcs.c -g -lm #-W -Wall #-ansi -pedantic 

main.o: main.c  
	gcc -o main.o -c main.c -g -lm #-W -Wall #-ansi -pedantic

clean:
	rm -rf *.o

