#Makefile
CC=gcc
DFLAGS=-Wall 
OMP=-lm -fopenmp -Ofast

all: run

run:
	$(CC) fft_parallel.c -o exec.o $(OMP)

#Create exec2 with debug flags on
debug:
	$(CC) $(DFLAGS) fft_parallel.c -o exec2.o $(OMP)

clean:
	rm -f *.o