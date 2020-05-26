#!/usr/bin/env bash

CLANG_VER=${CLANG_VER:-6.0.0}
CLANG_DIR=clang+llvm-$CLANG_VER-x86_64-linux-gnu-ubuntu-16.04
AFL_VER=${AFL_VER:-2.52b}
AFL_DIR=afl-$AFL_VER
AFL_EXE="afl-gcc afl-fuzz"

say_info() {
    echo "[+] $*" 1>&2
}

say_err() {
    [ -t 2 ] && [ -n "$TERM" ] \
        && echo "$(tput setaf 1)[-] $*$(tput sgr0)" 1>&2 \
        || echo "[-] $*" 1>&2
}

err() {
    if [[ $# -gt 0 ]]; then
        say_err $*
    fi
    exit 1
}

check_clang_version() {
    ACTUAL_CLANG_VER=$(clang --version | head -n 1 | \
        sed -e 's/clang version \(.*\) (.*)/\1/' \
        -e 's/clang version \(.*\)/\1/')

    if [[ $CLANG_VER != $ACTUAL_CLANG_VER ]]; then
        err "Expected clang version $CLANG_VER, got $ACTUAL_CLANG_VER"
    fi
}

check_afl_exe() {
    for bin in $AFL_EXE; do
        if ! [[ -e $AFL_DIR/$bin ]]; then
            err "$AFL_DIR/$bin not found. Check your installation"
        fi
    done
} 

say_info "Checking clang version..."
check_clang_version
say_info "Checking clang version... done."
say_info "Checking afl installation..."
check_afl_exe
say_info "Checking afl installation... done."
