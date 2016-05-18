

all: main

main:  funcs.o main.o
	gcc -o main main.o funcs.o 

funcs.o: funcs.c common.h
	gcc -o funcs.o -c funcs.c -W -Wall -ansi -pedantic 

main.o: main.c funcs.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

#commun.o: commo
clean:
	rm -rf *.o


	

#hello.o: hello.c
#	gcc -o hello.o -c hello.c -W -Wall -ansi -pedantic
#
#main.o: main.c hello.h
#	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
#
#clean:
#	rm -rf *.o
#
#mrproper: clean
#	rm -rf hello
