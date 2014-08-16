CC=gcc
LD=gcc

CC_INCLUDE=..
LD_INCLUDE=../mathlib/lib

CFLAGS=-I$(CC_INCLUDE) -pedantic -std=c90 -g -c -Wall
LDFLAGS=-L$(LD_INCLUDE)

collation: main.o solution00001 solution00002 solution00003 solution00004 solution00005 solution00006 solution00007 solution00008 mathlib.a
	$(CC) $(LDFLAGS) main.o ../solution/00001/solution.o ../solution/00002/solution.o ../solution/00003/solution.o ../solution/00004/solution.o ../solution/00005/solution.o ../solution/00006/solution.o ../solution/00007/solution.o ../solution/00008/solution.o -o collation.out -l:mathlib.a

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

solution00001:
	$(MAKE) -C ../solution/00001 solution.o
solution00002:
	$(MAKE) -C ../solution/00002 solution.o
solution00003:
	$(MAKE) -C ../solution/00003 solution.o
solution00004:
	$(MAKE) -C ../solution/00004 solution.o
solution00005:
	$(MAKE) -C ../solution/00005 solution.o
solution00006:
	$(MAKE) -C ../solution/00006 solution.o
solution00007:
	$(MAKE) -C ../solution/00007 solution.o
solution00008:
	$(MAKE) -C ../solution/00008 solution.o

mathlib.a: ../mathlib/src/* ../mathlib/include/*
	$(MAKE) -C ../mathlib/make

clean:
	rm -rf *.o collation.out
	$(MAKE) -C ../mathlib/make clean
	$(MAKE) -C ../solution/00001 clean
	$(MAKE) -C ../solution/00002 clean
	$(MAKE) -C ../solution/00003 clean
	$(MAKE) -C ../solution/00004 clean
	$(MAKE) -C ../solution/00005 clean
	$(MAKE) -C ../solution/00006 clean
	$(MAKE) -C ../solution/00007 clean
	$(MAKE) -C ../solution/00008 clean

