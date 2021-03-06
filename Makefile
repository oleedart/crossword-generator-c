# Makefile for Crossword puzzle
# Author: Oscar Lee

PROG = crossword
OBJS = crossword.o buildquestion.o file.o

# TESTING=-DTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: test clean

test: $(PROG)
	./$(PROG)

clean:
	rm -f core
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
	rm -f stocks
