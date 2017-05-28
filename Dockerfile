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
ENV WITH_TESTS 0

RUN $CC --version
RUN $CXX --version

RUN mkdir -p /build
#RUN cmake -H. -B/build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSKIP_PORTABILITY_TEST:BOOL="1" -DBuildTests:BOOL="0" -DWITH_CPP11:BOOL="1" -DCMAKE_BUILD_TYPE:STRING="Release" -DJUST_INSTALL_CEREAL:BOOL="1" -DUTPP_INCLUDE_TESTS_IN_BUILD:BOOL="0" -DDOCTEST_WITH_TESTS:BOOL="0" -DTEST_MODE:STRING="COMPARE" -DBUILD_TESTING:BOOL="0" -DTHREAD_SAFE:BOOL="1" -DCREATURE_WITH_TESTS:BOOL="$WITH_TESTS"
#RUN cmake --build /build --target creature_backend
#RUN if [ $WITH_TESTS -eq "ON" ]; then cmake --build /build --target creature_backend_test; fi

CMD /bin/bash; sleep infinity