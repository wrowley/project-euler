CC=gcc
CFLAGS=-c -Wall

solution.o: solution.c solution.h
	$(CC) $(CFLAGS) solution.c

main.o: main.c solution.h
	$(CC) $(CFLAGS) main.c

solve: solution.o main.o
	$(CC) $(LDFLAGS) solution.o main.o -o solve.out

clean:
	rm -rf *o solve.out
