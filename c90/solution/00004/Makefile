CC=gcc
INCLUDE=../..
CFLAGS=-c -Wall -I$(INCLUDE)

solve: solution.o main.o
	$(CC) $(LDFLAGS) solution.o main.o -o solve.out

solution.o: solution.c
	$(CC) $(CFLAGS) solution.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o solve.out
