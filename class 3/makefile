RS=rustc
RFLAGS=-O

all: twoscompl twiddling

twoscompl: twoscompl.rs
	$(RS) -o $@ $@.rs $(RFLAGS)

twiddling: twiddling.rs
	$(RS) -o $@ $@.rs $(RFLAGS)

clean:
	rm twoscompl
