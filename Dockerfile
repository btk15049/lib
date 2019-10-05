FROM ubuntu:latest

WORKDIR /opt


CMD bash -c "mkdir build && cd build && cmake .. && make && ctest -V"
