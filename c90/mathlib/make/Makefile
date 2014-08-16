CC=gcc
LD=ar
INCLUDE=..
CFLAGS=-I$(INCLUDE) -pedantic -std=c90 -g -c -Wall
LDFLAGS=cr

mathlib.a: extuint.o
	$(LD) $(LDFLAGS) ../lib/mathlib.a extuint.o

extuint.o: ../src/extuint.c ../include/extuint.h
	$(CC) $(CFLAGS) ../src/extuint.c

clean:
	rm -rf *.o ../lib/mathlib.a
