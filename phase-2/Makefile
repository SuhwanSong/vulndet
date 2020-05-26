AFL_VER=2.52b
AFL_DIR=$(CURDIR)/../afl-$(AFL_VER)
AFL_CC=$(AFL_DIR)/afl-gcc
AFL_FUZZ=$(AFL_DIR)/afl-fuzz
LIBFUZZ_CFLAGS=-fsanitize=fuzzer
LIBFUZZ_ASAN_CFLAGS=-fsanitize=fuzzer,address
CLANG=clang

.PHONY: all clean

all: app app-afl stack-fuzzer heap-fuzzer uaf-fuzzer

app: main.cc uaf.cc
	$(CLANG) -o $@ $^ -std=c++11

app-afl: main.cc uaf.cc
	$(AFL_CC) -fsanitize=address $^ -o $@ -std=c++11

stack-fuzzer: stack-fuzzer.cc
	$(CLANG) $(LIBFUZZ_ASAN_CFLAGS) $^ -o $@ -std=c++11

heap-fuzzer: heap-fuzzer.cc
	$(CLANG) $(LIBFUZZ_ASAN_CFLAGS) $^ -o $@ -std=c++11

uaf-fuzzer: uaf-fuzzer.cc uaf.cc
	$(CLANG) $(LIBFUZZ_ASAN_CFLAGS) $^ -o $@ -std=c++11

run-afl: app-afl
	$(AFL_FUZZ)	-i $(CURDIR)/input -o $(CURDIR)/output -- $(CURDIR)/$^ @@

clean:
	$(RM) -rf app app-afl stack-fuzzer heap-fuzzer uaf-fuzzer
