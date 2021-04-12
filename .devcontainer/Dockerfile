ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

WORKDIR /opt

RUN apt update -y && apt upgrade -y \
    && apt-get install -y software-properties-common \
    && apt-add-repository ppa:fish-shell/release-3 \
    && apt-add-repository ppa:git-core/ppa
RUN apt update -y && apt upgrade -y \
    && apt-get install -y \
    build-essential \
    fish \
    g++-9 \
    libssl-dev \
    python3-pip \
    clang-format \
    && apt-get clean

ENV CC gcc-9
ENV CXX g++-9
ENV CXXFLAGS -std=c++17

# setup g++
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 30
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 30

# setup cmake
RUN git clone https://gitlab.kitware.com/cmake/cmake.git \
    && cd cmake \
    && git checkout v3.19.5 \
    && ./bootstrap \
    && make -j8 \
    && make install \
    && cd .. && rm -rf cmake

#setup boost
RUN git clone https://github.com/boostorg/boost.git \
    && cd boost \
    && git checkout boost-1.75.0 \
    && git submodule update --init \
    && ./bootstrap.sh \
    && ./b2 toolset=gcc-9 --prefix=/usr/local -j5 \
    && ./b2 install toolset=gcc-9 --prefix=/usr/local -j5 \
    && cd .. && rm -rf boost

RUN git clone https://github.com/atcoder/ac-library.git \
    && cp -r ac-library/atcoder /usr/include/atcoder

