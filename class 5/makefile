CC=g++
CFLAGS=-O -std=c++17 -Wall -pedantic

all: smooth exp

smooth: smooth.cpp

exp: exp.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm smooth exp
