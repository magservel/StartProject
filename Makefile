CGLAGS =-lm -pg -g -std=c99 -W -Wall 
#-O3 -funroll-loops -ftree-vectorize -march=native


all: main

main: funcs.o main.o
	gcc -o main funcs.o main.o $(CGLAGS)

funcs.o: funcs.c
	gcc -o funcs.o -c funcs.c $(CGLAGS)

main.o: main.c funcs.h
	gcc -o main.o -c main.c $(CGLAGS)

clean:
	rm -rf *.o

