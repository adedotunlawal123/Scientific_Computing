RS=rustc
RSFLAGS=-O

all: rng pi pi-mp

rng: rng.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

pi: pi.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

pi-mp: pi-mp.rs
	$(RS) -o $@ $@.rs $(RSFLAGS)

clean:
	rm rng pi pi-mp

