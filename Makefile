.PHONY: all lib debug

all: lib

lib:
	gcc -g -c -fPIC *.c
	ar rcs libnm.a *.o

a.out: 
	gcc -o prog main.c -I.  -L. -lnm
debug:
	gcc -g -o prog main.c -L. -lnm
