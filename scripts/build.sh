#!/bin/bash

cmake --build $BUILD_PATH --target creature_backend -- -j2
if [ "${BUILD_ONLY}" != "1" ]; then cmake --build $BUILD_PATH --target creature_backend_build_test -- -j2; fi