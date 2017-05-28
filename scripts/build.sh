#!/bin/bash

cmake --build $BUILD_PATH --target creature_backend
if [[ -n $WITH_TESTS && ("$WITH_TESTS" == "1" || "$WITH_TESTS" == "ON") ]]; then cmake --build $BUILD_PATH --target creature_backend_test; fi
if [[ -n $WITH_TESTS && ("$WITH_TESTS" == "1" || "$WITH_TESTS" == "ON") ]]; then cd $BUILD_PATH/backend && ctest -R ".*creature_backend.*"; fi