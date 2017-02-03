#Makefile

#Define Compiler
CC=gcc
#These flags included for debugging
debflags= -g -Wall

#Execute these Rules
all: askisi1 askisi2

#Exercise 1 compilation
askisi1:
	$(CC) askisi1.c -o exec1.o -lm
	
#Exercise 2 compilation
askisi2:
	$(CC) askisi2.c -o exec2.o 

#For debugging purposes only
debug:
	$(CC) $(debflags) askisi1.c -o exec1.o -lm
	$(CC) $(debflags) askisi2.c -o exec2.o 

#Removes Object files
clean:
	rm -f *.o
