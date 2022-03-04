CC=g++
CFLAGS=-O2 -std=c++17 -Wno-deprecated-declarations
GLFLAGS=`./glflags.bash`

EXE=cannon catenary string-fit

all: $(EXE)

cannon: cannon.o cannon_openGL.o
	$(CC) -o $@ cannon.o cannon_openGL.o $(LDFLAGS) $(GLFLAGS)

cannon.o: cannon.cpp
	$(CC) -c cannon.cpp $(CFLAGS)

cannon_openGL.o: cannon_openGL.cpp cannon.h
	$(CC) -c cannon_openGL.cpp $(CFLAGS)

catenary: catenary.o catenary-openGL.o
	$(CC) -o $@ catenary.o catenary-openGL.o $(LDFLAGS) $(GLFLAGS)

catenary.o: catenary.cpp
	$(CC) -c catenary.cpp $(CFLAGS)

catendary-openGL.o: catenary-openGL.cpp catenary.h
	$(CC) -c catenary-openCL.cpp $(CFLAGS)

string-fit: string-fit.cpp mtrand.hpp
	$(CC) -o $@ string-fit.cpp $(CFLAGS)

clean:
	rm $(EXE) *.o 2>&-

