CC=g++
CFLAGS=-O -pedantic -Wall -std=c++17

linalg: linalg.cpp matrix.hpp matrix_upper_tri.hpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm linalg

