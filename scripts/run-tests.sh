#!/bin/bash

if [ "${BUILD_ONLY}" != "1" ]; then cmake --build $BUILD_PATH --target creature_backend_check; fi
if [ "${COVERAGE}" = "1" ]; then bash <(curl -s https://raw.githubusercontent.com/codecov/codecov-bash/master/codecov) -x $GCOV -a "-s `pwd`" ; fi