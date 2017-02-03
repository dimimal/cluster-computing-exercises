#Makefile of Project 3

#This is the compiler to use
CC = mpicc
DFLAGS = -g -Wall
LDFLAGS = -lm -lrt


# make all will create all executables
all: serial parallel

#This rule creates the serial executable
serial: serial_lib.h
	$(CC) $(CFLAGS) serialCOO.c coo_functions.c -o $@.o $(LDFLAGS)

# This is the rule creates the parallel executable 
parallel: parallel_lib.h
	$(CC) $(CFLAGS) parallelMatVectMul.c parallel_func.c -o $@.o $(LDFLAGS)

# make clean will remove all executables 
clean:
	rm -f *.o
