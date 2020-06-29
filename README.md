# About
This is a version of [libc-test](https://wiki.musl-libc.org/libc-test.html)
meant to test the [musl](https://github.com/microsoft/checkedc-musl) C library
which has been converted to [Checked C](https://github.com/Microsoft/checkedc).
The sources here have been mirrored from [this](git://repo.or.cz/libc-test)
repo. This version of `libc-test` is meant to compile with the
[checkedc-clang](https://github.com/microsoft/checkedc-clang) compiler. It is
also meant to link against a pre-built
[compiler-rt](https://compiler-rt.llvm.org) downloaded from
[llvm.org](https://releases.llvm.org/download.html).

# Usage

## Set up compiler-rt

`libc-test` needs `compiler-rt` for the runtime libraries. We download the 10.0
version of the pre-built `compiler-rt` for Ubuntu from llvm.org.
```
export RT_PATH=</some/dir>
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz 
tar -xvf clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz -C $RT_PATH --strip 1
```

## Build musl with Checked C clang

```
export PATH=</path/to/checkedc-clang/bin>
cd </some/dir>
git clone https://github.com/microsoft/checkedc-musl.git src
mkdir build && cd build
CC=clang CFLAGS=-fPIC LDFLAGS=-fPIC ../src/configure --prefix=$PWD --disable-shared 
make clean && make -j32 && make install
```

## Build libc-test

Note: Make sure the environment variables `MUSL_PATH` and `RT_PATH` are set.
```
export PATH=</path/to/checkedc-clang/bin>
git clone https://github.com/microsoft/checkedc-libc-test.git
cd checkedc-libc-test
make clean && make -j32 2>&1 | tee log
```

# Results of libc-test

After building and running `libc-test` check if any errors have occurred. There
should be 0 errors found in the log file.
`grep error: log | wc -l`

Next, check what tests have failed, if any.
```grep ^FAIL log | wc -l```

Note: At the time of writing this README, there were 62 known failures in `libc-test`.

To check if an error in your `musl` would produce errors in `libc-test`, you
can do the following:
- Add an error to your `musl` sources (like in `src/string/strchr.c`)
- Rebuild `musl`
- Rebuild `libc-test`
- `grep ^FAIL log | wc -l`
