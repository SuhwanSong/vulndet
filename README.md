Lab: Vulnerability Detection
============================================

In this assignment you will have hands-on experiences with fuzzing;
an automated testing technique. Specifically you will learn how to
use AFL and how to write fuzzer driver used by LibFuzzer.

### Setup
```
$ vagrant box add ubuntu/xenial64
$ vagrant init ubuntu/xenial64
$ vagrant up
$ vagrant ssh
```

```
$ git clone https://github.com/SuhwanSong/vulndet.git
$ cd vulndet
$ source ./setup.sh
$ ./check-install.sh
```


### 1. Fuzzing with AFL

In `phase-1`, you will find `test.c` source code. You can choose to compile
it into `bin-weak` with weak a constraint or `bin-strong` with strong a constraint
based on your compilation command. In this phase you are going to learn how to
fuzz a target binary using AFL.

```
$ afl-fuzz -i ./input -o ./output -- <target> @@
```

### 2. (Manually) Weakening Hard Constraints

Probably you now find out that vulnerabilities in the binary with strong constaint
is hard to be discovered. Now look at the source code `test.c` and manually update
the source code so that the fuzzer can easily detect the bug with out compromising
the semantic meaning of the program.

**Question**: In practice manually updating checks in the source code is _not_
scalable at all. Can we automate these processes of transforming the program?
Is it still possible even if we are not provided with the source code?

### 3. LibFuzzer + AddressSanitizer

LibFuzzer is an in-process fuzzing engine, which is the part of the LLVM project.
In the directory `phase-2`, you will find `stack-fuzzer.cc` and `heap-fuzzer.cc`.
If you open the source code, you will see simple _fuzzer drivers_:
```cxx
extern "C" int LLVMFuzzerTestOneInput(const unit8_t* data, size_t size) {
    vuln(data, size);
    return 0;
}
```
When copmiled with `-fsanitize=fuzzer` option, the output executable will
continuously run `LLVMFuzzerTestOneInput` with different data, until it finds
a vulnerability or a crash. You can also use `-fsanitize=address` option
to enable AddressSanitizer.

### 4. Find Bugs using AFL and LibFuzzer

In `phase-2`, you will find a vlunerable source code `main.cc`. Your task
is to first find the bugs in the program by auditing the code. Was it easy?
Now you are going to find these vulnerability with fuzzers; AFL and LibFuzzer.
To fuzz the binary with AFL might want to compile `main.cc` with `afl-gcc`
with `-fsanitize=address` option. If you are using AddressSanitizer with AFL
don't forget to specify `-m none` option, otherwise AFL will complain about
the memory limits.

## References
* [American Fuzzy Lop](http://lcamtuf.coredump.cx/afl/)
* [LLVM libFuzzer](https://llvm.org/docs/LibFuzzer.html)
* [Google Fuzzer Test Suite](https://github.com/google/fuzzer-test-suite)

