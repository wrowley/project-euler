CC=gcc
INCLUDE=..
CFLAGS=-c -Wall -I$(INCLUDE)

collation: main.o solution00003 solution00004
	$(CC) $(LDFLAGS) main.o ../solution/00003/solution.o ../solution/00004/solution.o -o collation.out

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

solution00003:
	$(MAKE) -C ../solution/00003 solution.o

solution00004:
	$(MAKE) -C ../solution/00004 solution.o

clean:
	rm -rf *.o collation.out
