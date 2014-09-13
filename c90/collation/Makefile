CC=gcc
LD=gcc

CC_INCLUDE=..
LD_INCLUDE=../mathlib/lib

CFLAGS=-I$(CC_INCLUDE) -pedantic -std=c90 -g -c -Wall
LDFLAGS=-L$(LD_INCLUDE)

collation: main.o solution00001 solution00002 solution00003 solution00004 solution00005 solution00006 solution00007 solution00008 solution00009 solution00010 solution00011 solution00012 solution00013 mathlib.a
	$(CC) $(LDFLAGS) main.o ../solution/00001/solution.o ../solution/00002/solution.o ../solution/00003/solution.o ../solution/00004/solution.o ../solution/00005/solution.o ../solution/00006/solution.o ../solution/00007/solution.o ../solution/00008/solution.o ../solution/00009/solution.o ../solution/00010/solution.o ../solution/00011/solution.o ../solution/00012/solution.o ../solution/00013/solution.o -o collation.out -l:mathlib.a

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
solution00009:
	$(MAKE) -C ../solution/00009 solution.o
solution00010:
	$(MAKE) -C ../solution/00010 solution.o
solution00011:
	$(MAKE) -C ../solution/00011 solution.o
solution00012:
	$(MAKE) -C ../solution/00012 solution.o
solution00013:
	$(MAKE) -C ../solution/00013 solution.o

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
	$(MAKE) -C ../solution/00009 clean
	$(MAKE) -C ../solution/00010 clean
	$(MAKE) -C ../solution/00011 clean
	$(MAKE) -C ../solution/00012 clean
	$(MAKE) -C ../solution/00013 clean
