FROM ubuntu:latest


WORKDIR /opt

RUN apt-get update \
    # apt-get
    && apt-get -y install \
    build-essential \
    curl \
    file \
    gcc-5 \
    git \
    g++-5 \
    libssl-dev \
    # 不要なキャッシュを削除
    && apt-get clean

ENV CC gcc-5
ENV CXX g++-5

    # boost install
RUN git clone --recursive https://github.com/boostorg/boost.git \
    && cd boost \
    && ./bootstrap.sh \
    && ./b2 toolset=gcc-5 --prefix=/usr/local -j5 \
    && ./b2 install toolset=gcc-5 --prefix=/usr/local -j5 \
    && cd .. \
    && rm -rf boost/

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
CMD [ bash -c "mkdir build && cd build && cmake .. && make && ctest -V" ]
