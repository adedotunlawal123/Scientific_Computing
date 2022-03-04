CC=g++
CFLAGS=-O2 -pedantic -Wall -lm -std=c++17

EXE=orbit orbit_vel

all: $(EXE)

orbit: orbit.cpp

orbit_vel: orbit_vel.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm $(EXE)

