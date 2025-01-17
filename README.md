# WARNING: THIS IS SUPER MEGA EXTRA ALPHA VERSION OF C++ DRIVER FOR YDB!!!
# Don't use it in production environment!

If you ok with this warning, then...

# Building YDB C++ SDK from sources

## Prerequisites

- cmake 3.22+
- llvm 16+
- git 2.20+
- ninja 1.10+
- ragel
- yasm
- protoc

## Library dependencies

- gRPC
- protobuf
- OpenSSL
- Iconv
- IDN
- rapidjson
- xxhash
- zlib
- zstd
- lz4
- snappy 1.1.8+
- base64

## Runtime requirements

- libidn11-dev (IDN)
- libiconv (Iconv)

## Install dependencies

```bash
sudo apt-get -y update
sudo apt-get -y install git cmake ninja-build libidn11-dev ragel yasm protobuf-compiler \
  protobuf-compiler-grpc libprotobuf-dev libgrpc++-dev libgrpc-dev libgrpc++1 libgrpc10 \
  rapidjson-dev zlib1g-dev libxxhash-dev libzstd-dev libsnappy-dev liblz4-dev

wget https://apt.llvm.org/llvm.sh
chmod u+x llvm.sh
sudo ./llvm.sh 16

wget https://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.15.tar.gz
tar -xvzf libiconv-1.15.tar.gz
cd libiconv-1.15
./configure --prefix=/usr/local
sudo make
sudo make install

sudo wget https://github.com/aklomp/base64/archive/refs/tags/v0.5.2.tar.gz
sudo tar -xvzf v0.5.2.tar.gz
cd base64-0.5.2
sudo mkdir build
cd build
sudo cmake ..
sudo cmake --build . --target install
cd ../../

```

## Create the work directory

```bash
mkdir ~/ydbwork && cd ~/ydbwork
mkdir build
```

## Install ccache

Install `ccache` into `/usr/local/bin/`. The recommended version is `4.8.1` or above, the minimum required version is `4.7`.

```bash
(V=4.8.1; curl -L https://github.com/ccache/ccache/releases/download/v${V}/ccache-${V}-linux-x86_64.tar.xz | \
sudo tar -xJ -C /usr/local/bin/ --strip-components=1 --no-same-owner ccache-${V}-linux-x86_64/ccache)
```

## Clone the ydb-cpp-sdk repository

```bash
git clone https://github.com/ydb-platform/ydb-cpp-sdk.git
```

## Configure

Generate build configuration using `ccache`

```bash
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DCCACHE_PATH=/usr/local/bin/ccache \
-DCMAKE_TOOLCHAIN_FILE=../ydb-cpp-sdk/clang.toolchain \
../ydb-cpp-sdk
```

## Build

```bash
cd build
ninja
```
