.PHONY: all lib debug

all: lib SoD

lib:
	gcc -g -c -fPIC *.c
	ar rcs libnm.a *.o

SoD: lire.o
	gcc -o prog main.c lire.o -I.  -L. -lnm

lire.o: lire.c lire.h
	gcc -c -o lire.o lire.c -I.  -L. -lnm

debug:
	gcc -g -o prog main.c -L. -lnm
