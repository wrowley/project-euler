CC=gcc
INCLUDE=../..
CFLAGS=-g -c -Wall -I$(INCLUDE)

solve: solution.o main.o
	$(CC) $(LDFLAGS) solution.o main.o -o solve.out

solution.o: solution.c solution.h
	$(CC) $(CFLAGS) solution.c

main.o: main.c solution.h
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *o solve.out
