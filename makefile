CC=gcc
CFLAGS=-Wall -ansi -pedantic -Iincludes 
DEP = text.h

all: text

text: text.c
	$(CC) $(CFLAGS) -c text.c -o text.o

clean:
	rm text.o