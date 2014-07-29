CC=gcc
INCLUDE=..
CFLAGS=-c -Wall -I$(INCLUDE)

collation: main.o solution00001 solution00002
	$(CC) $(LDFLAGS) main.o ../solution/00001/solution.o ../solution/00002/solution.o -o collation.out

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

solution00001:
	$(MAKE) -C ../solution/00001 solution.o

solution00002:
	$(MAKE) -C ../solution/00002 solution.o

clean:
	rm -rf *.o collation.out
