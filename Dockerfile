FROM ubuntu:16.04

ADD ./backend/ /project/backend/
ADD ./scripts/ /project/scripts/
ADD ./tools/ /project/tools/
ADD ./CMakeLists.txt /project/CMakeLists.txt
ADD ./VERSION /project/VERSION
WORKDIR /project

RUN apt-get -qq update \
    && apt-get -qq install -y gcc g++ clang cmake make binutils \
	&& ./scripts/install-deps.sh \
 && rm -rf /var/lib/apt/lists/*

ENV CC gcc
ENV CXX g++
ENV BUILD_TYPE Release
ENV GCOV gcov

RUN $CC --version
RUN $CXX --version
RUN $GCOV --version

RUN mkdir -p /build

CMD /bin/bash; sleep infinity