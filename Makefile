CC = gcc
CFLAGS = -Wall -O2

all: main

main: main.o lib_ppm.o
	$(CC) $(CFLAGS) -o main main.o lib_ppm.o -lm

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

lib_ppm.o: lib_ppm.c
	$(CC) $(CFLAGS) -c lib_ppm.c

clean:
	rm -f *.o main *.ppm
