CC=gcc
INCLUDE=..
CFLAGS=-c -Wall -I$(INCLUDE)

collation: main.o solution00001 solution00002 solution00003 solution00004 solution00005 solution00006 solution00007
	$(CC) $(LDFLAGS) main.o ../solution/00001/solution.o ../solution/00002/solution.o ../solution/00003/solution.o ../solution/00004/solution.o ../solution/00005/solution.o ../solution/00006/solution.o ../solution/00007/solution.o -o collation.out

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

clean:
	rm -rf *.o collation.out
	$(MAKE) -C ../solution/00001 clean
	$(MAKE) -C ../solution/00002 clean
	$(MAKE) -C ../solution/00003 clean
	$(MAKE) -C ../solution/00004 clean
	$(MAKE) -C ../solution/00005 clean
	$(MAKE) -C ../solution/00006 clean
	$(MAKE) -C ../solution/00007 clean

