CC=g++
CFLAGS=-O -std=c++17 -pedantic -Wall

all: bisection newton matrices

bisection: bisection.cpp

newton: newton.cpp

matdef.o: matdef.cpp matdef.hpp
	$(CC) -c matdef.cpp

matrices.o: matrices.cpp
	$(CC) -c matrices.cpp

matrices: matrices.o matdef.o
	$(CC) -o $@ matrices.o matdef.o

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm bisection newton matrices matdef.o matrices.o

