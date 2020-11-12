#!/usr/bin/env bash

say_info() {
    echo "[+] $*" 1>&2
}

install_clang() {
    CLANG_VER=6.0.0
    CLANG_DIR=clang+llvm-$CLANG_VER-x86_64-linux-gnu-ubuntu-16.04

    clang --version > /dev/null

    # If clang installation is found. Ask the user
    if [[ $? -eq 0 ]]; then
        ACTUAL_CLANG_VER=$(clang --version | head -n 1 | \
            sed -e 's/clang version \(.*\) (.*)/\1/' \
            -e 's/clang version \(.*\)/\1/')

        say_info "Found a clang installation (version=$CLANG_VER)."
        while true; do
            read -r -p "Do you want to proceed? [Y/n] " ans
            case $ans in
                [Yy]) { break; } ;;
                [Nn]) { exit 1; } ;;
                *)    { continue; } ;;
            esac
        done
    fi

    if ! [[ -e $CLANG_DIR.tar.xz  ]]; then
        wget http://releases.llvm.org/6.0.0/$CLANG_DIR.tar.xz
    fi

    tar xf $CLANG_DIR.tar.xz
    sudo rm -rf /usr/local/bin/clang* /usr/local/lib/clang
    sudo cp -rf $CLANG_DIR/bin/* /usr/local/bin
    sudo cp -rf $CLANG_DIR/lib/clang /usr/local/lib
    rm -rf $CLANG_DIR
}

install_deps() {
    sudo apt update
    sudo apt install -y curl gcc g++ make zlib1g-dev vim
}

get_afl() {
    AFL_VER=2.52b
    AFL_DIR=afl-$AFL_VER

    if ! [[ -e $AFL_DIR.tgz ]]; then
        wget http://lcamtuf.coredump.cx/afl/releases/$AFL_DIR.tgz
    fi

    tar xvf ./afl-$AFL_VER.tgz
    pushd ./afl-$AFL_VER
    make -j`nproc`
    popd
}

setup_env() {
    export PATH=$PATH:`pwd`/$AFL_DIR
}

main() {
    SKIP_CLANG=false

    if [[ $# -gt 0 ]]; then
        case $1 in
            --skip-clang) { SKIP_CLANG=true; } ;;
        esac
    fi

    if [[ $SKIP_CLANG == false ]]; then
        install_clang
    else
        say_info "Skipping clang installation"
    fi

    install_deps
    get_afl
    say_info "All installation finished. Setting up environment..."
    sudo su -c ./cpu
    setup_env
    say_info "Environment setting done! You are ready to go!"
}

main $*
