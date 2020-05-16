FROM ubuntu:latest

WORKDIR /opt

RUN apt-get update \
    # apt-get
    && apt-get -y install \
    build-essential \
    curl \
    file \
    gcc-9 \
    git \
    g++-9 \
    libssl-dev \
    # 不要なキャッシュを削除
    && apt-get clean

ENV CC gcc-9
ENV CXX g++-9

# boost install
RUN curl -OL https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz \
    && tar xvfz ./boost_1_72_0.tar.gz \
    && cd boost* \
    && ./bootstrap.sh \
    && ./b2 toolset=gcc-5 --prefix=/usr/local -j5 \
    && ./b2 install toolset=gcc-5 --prefix=/usr/local -j5 \
    && cd .. \
    && rm -rf boost*

# cmake install
RUN git clone https://gitlab.kitware.com/cmake/cmake.git \
    && cd cmake \
    && ./bootstrap --prefix=/usr/local \
    && make -j5 \
    && make install \
    && cd .. \
    && rm -rf cmake \
    && mkdir /app

ENV CMAKE_ROOT /usr/local/share/cmake-3.15
WORKDIR /app

CMD bash -c "mkdir build && cd build && cmake .. && make && ctest -V"
