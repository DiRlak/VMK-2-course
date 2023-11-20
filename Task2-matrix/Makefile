CFLAGS=gcc -c -Werror -Wall -g

all: full

full: matrix main
	gcc matrix.o main.o

matrix:
	 $(CFLAGS) matrix.h matrix.c

main:
	 $(CFLAGS) main.c

clean:
	rm -rf *.o full
