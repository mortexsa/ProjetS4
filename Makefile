.PHONY: all lib debug

all: lib SoD

lib:
	gcc -g -c -fPIC *.c
	ar rcs libnm.a *.o

SoD: lire.o jouer.o
	gcc -o SoD main.c lire.o jouer.o -I.  -L. -lnm -lm

jouer.o: jouer.c jouer.h
	gcc -c -o jouer.o jouer.c -I. -L. -lnm -lm

lire.o: lire.c lire.h
	gcc -c -o lire.o lire.c -I.  -L. -lnm -lm

debug:
	gcc -g -o prog main.c -L. -lnm -lm
