CC=g++
EXE=pairs corners pi integrate
CFLAGS=-O2 -std=c++17 -pedantic -Wall -lm

all: $(EXE)

pairs: pairs.cpp mtrand.hpp

corners: corners.cpp mtrand.hpp

pi: pi.cpp mtrand.hpp

integrate: integrate.cpp integrate.cpp

.cpp:
	$(CC) -o $@ $@.cpp $(CFLAGS)

clean:
	rm $(EXE)
