#!/bin/bash

cmake --build $BUILD_PATH --target creature_backend
if [ "${BUILD_ONLY}" != "1" ]; then cmake --build $BUILD_PATH --target creature_backend_test -- -j2; fi
if [ "${BUILD_ONLY}" != "1" ]; then cd $BUILD_PATH/backend && ctest -R ".*creature_backend.*"; fi
if [ "${COVERAGE}" = "1" ]; then bash <(curl -s https://raw.githubusercontent.com/codecov/codecov-bash/master/codecov) -x $GCOV -a "-s `pwd`" ; fi