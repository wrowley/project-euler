CC=gcc
CFLAGS=-c -Wall

solution.o:
	$(CC) $(CFLAGS) solution.c

main.o:
	$(CC) $(CFLAGS) main.c

solve: solution.o main.o
	$(CC) $(LDFLAGS) solution.o main.o -o $@

clean:
	rm -rf *o solve