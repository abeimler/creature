#!/bin/bash

cmake --build $BUILD_PATH --target creature_backend -- -j2
if [ "${BUILD_ONLY}" != "1" ]; then cmake --build $BUILD_PATH --target creature_backend_build_test -- -j2; fi
if [ "${BUILD_ONLY}" != "1" ]; then cmake --build $BUILD_PATH --target creature_backend_check; fi
if [ "${COVERAGE}" = "1" ]; then bash <(curl -s https://raw.githubusercontent.com/codecov/codecov-bash/master/codecov) -x $GCOV -a "-s `pwd`" ; fi