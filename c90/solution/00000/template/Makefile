CC=gcc
LD=gcc

CC_INCLUDE=../..
LD_INCLUDE=../../mathlib/lib

CFLAGS=-I$(CC_INCLUDE) -pedantic -std=c90 -g -c -Wall
LDFLAGS=-L$(LD_INCLUDE)

solve: solution.o main.o mathlib.a
	$(LD) $(LDFLAGS) -o solve.out solution.o main.o -l:mathlib.a

solution.o: solution.c
	$(CC) $(CFLAGS) solution.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

mathlib.a: ../../mathlib/src/* ../../mathlib/include/*
	$(MAKE) -s -C ../../mathlib/make

clean:
	rm -rf *.o solve.out
