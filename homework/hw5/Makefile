# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)


# TODO: Add a target to create the hw5 executable here


# Compiles hw5.cpp into an object file
hw5.o: hw5.cpp language_model.h
	$(CC) $(CFLAGS) -c hw5.cpp

# Compiles language_model.cpp into an object file
language_model.o: language_model.cpp language_model.h
	$(CC) $(CFLAGS) -c language_model.cpp

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o hw5
