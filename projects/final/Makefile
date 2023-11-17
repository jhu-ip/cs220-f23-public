CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -pedantic

%.o : %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o

C_SRCS = pnglite.c
CXX_SRCS = main.cpp plot.cpp bounds.cpp image.cpp exception.cpp \
	reader.cpp renderer.cpp expr.cpp expr_parser.cpp func.cpp \
	fill.cpp

OBJS = $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)

plot : $(OBJS)
	$(CXX) -o $@ $(OBJS) -lm -lz

clean :
	rm -f *.o plot

depend :
	$(CC) -M $(CFLAGS) $(C_SRCS) > depend.mak
	$(CXX) -M $(CXXFLAGS) $(CXX_SRCS) >> depend.mak

depend.mak :
	touch $@

include depend.mak
