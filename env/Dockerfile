FROM ubuntu:latest

RUN apt-get update \
    # apt-get
    && apt-get -y install \
    build-essential \
    curl \
    file \
    gcc-5 \
    git \
    g++-5 \
    # 不要なキャッシュを削除
    && apt-get clean
