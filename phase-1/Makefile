AFL_FUZZ := ${CURDIR}/../afl-2.52b/afl-fuzz
AFL_CC := ${CURDIR}/../afl-2.52b/afl-gcc
AFL_CFLAGS := -O3 -funroll-loops # See afl-gcc.c

all: bin-weak bin-strong

bin-weak: test.c
	$(CC) $(AFL_CFLAGS) $< -DCOND_WEAK -o $@

bin-strong: test.c
	$(CC) $(AFL_CFLAGS) $< -o $@

afl-bin-weak: test.c
	$(AFL_CC) -O0 $< -DCOND_WEAK -o $@

afl-bin-strong: test.c
	$(AFL_CC) -O0 $< -o $@

runafl-weak: afl-bin-weak
	$(AFL_FUZZ) -i $(CURDIR)/input -o $(CURDIR)/output-weak -- $(CURDIR)/$< @@

runafl-strong: afl-bin-strong
	$(AFL_FUZZ) -i $(CURDIR)/input -o $(CURDIR)/output-strong -- $(CURDIR)/$< @@

.phony: bin-weak bin-strong afl-bin-weak afl-bin-strong runafl-weak runafl-strong clean

clean:
	$(RM) -rf *bin-weak *bin-strong output-weak output-strong
