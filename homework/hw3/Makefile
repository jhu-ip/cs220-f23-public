# Homework 3
GCC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

hw3: hw3.o functions.o
	$(GCC) -o hw3 hw3.o functions.o

hw3.o: hw3.c functions.h
	$(GCC) -c hw3.c $(CFLAGS)

# TODO: instructions to compile and run the test file

clean:
	rm -f *.o hw3 test *~
