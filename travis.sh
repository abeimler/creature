#!/usr/bin/env bash

DEPS_DIR=${TRAVIS_BUILD_DIR}/deps
USER_PATH_DIR=~/bin
TEMP_DIR=~/.cmake

mkdir -p ${USER_PATH_DIR}
mkdir -p ${TEMP_DIR}
mkdir -p ${DEPS_DIR}

cd "${DEPS_DIR}"

############################################################################
# Install a recent CMake (unless already installed on OS X)
############################################################################
if [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
    if [[ -z "$(ls -A ${DEPS_DIR}/cmake/bin)" ]]; then
    CMAKE_URL="https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.tar.gz"
    mkdir -p cmake && travis_retry wget --no-check-certificate --quiet -O - "${CMAKE_URL}" | tar --strip-components=1 -xz -C cmake
    fi
    export PATH="${DEPS_DIR}/cmake/bin:${PATH}"
else
    if ! brew ls --version cmake &>/dev/null; then brew install cmake; fi
fi

############################################################################
# [linux]: Install the right version of libc++
############################################################################
if [[ -n "$CLANG_VERSION" && "${TRAVIS_OS_NAME}" == "linux" && "${STDLIB}" != "libstdc++" ]]; then
    if [[ "$CLANG_VERSION" == "3.5" ]]; then LLVM_VERSION="3.5.2"; fi
    if [[ "$CLANG_VERSION" == "3.6" ]]; then LLVM_VERSION="3.6.2"; fi
    if [[ "$CLANG_VERSION" == "3.7" ]]; then LLVM_VERSION="3.7.1"; fi
    if [[ "$CLANG_VERSION" == "3.8" ]]; then LLVM_VERSION="3.8.1"; fi
    if [[ "$CLANG_VERSION" == "3.9" ]]; then LLVM_VERSION="3.9.0"; fi
    LLVM_ROOT="${DEPS_DIR}/llvm-${LLVM_VERSION}"
    LLVM_URL="http://llvm.org/releases/${LLVM_VERSION}/llvm-${LLVM_VERSION}.src.tar.xz"
    LIBCXX_URL="http://llvm.org/releases/${LLVM_VERSION}/libcxx-${LLVM_VERSION}.src.tar.xz"
    LIBCXXABI_URL="http://llvm.org/releases/${LLVM_VERSION}/libcxxabi-${LLVM_VERSION}.src.tar.xz"
    if [[ -z "$(ls -A ${LLVM_ROOT}/install/include)" ]]; then
    mkdir -p "${LLVM_ROOT}" "${LLVM_ROOT}/build" "${LLVM_ROOT}/projects/libcxx" "${LLVM_ROOT}/projects/libcxxabi"
    travis_retry wget --quiet -O - "${LLVM_URL}" | tar --strip-components=1 -xJ -C "${LLVM_ROOT}"
    travis_retry wget --quiet -O - "${LIBCXX_URL}" | tar --strip-components=1 -xJ -C "${LLVM_ROOT}/projects/libcxx"
    travis_retry wget --quiet -O - "${LIBCXXABI_URL}" | tar --strip-components=1 -xJ -C "${LLVM_ROOT}/projects/libcxxabi"
    (cd "${LLVM_ROOT}/build" && cmake .. -DCMAKE_CXX_COMPILER="$CXX" -DCMAKE_C_COMPILER="$CC" -DCMAKE_INSTALL_PREFIX="${LLVM_ROOT}/install" -DCMAKE_BUILD_TYPE=$BUILD_TYPE)
    (cd "${LLVM_ROOT}/build/projects/libcxx" && make install -j$JOBS)
    (cd "${LLVM_ROOT}/build/projects/libcxxabi" && make install -j$JOBS)
    fi
    export CXXFLAGS="-I ${LLVM_ROOT}/install/include/c++/v1"
    export LDFLAGS="-L ${LLVM_ROOT}/install/lib -lc++ -lc++abi"
    export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${LLVM_ROOT}/install/lib"
fi
    