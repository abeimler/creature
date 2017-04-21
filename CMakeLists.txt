# Copyright (C) 2016 Jonathan Müller <jonathanmueller.dev@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

cmake_minimum_required(VERSION 3.1)
project(DEBUG_ASSERT)

# options
option(DEBUG_ASSERT_NO_STDIO "whether or not the default_handler uses fprintf() to print an error message" OFF)
if(DEBUG_ASSERT_NO_STDIO)
    set(_debug_assert_no_stdio DEBUG_ASSERT_NO_STDIO)
endif()

option(DEBUG_ASSERT_DISABLE "completely disable assertion macro" OFF)
if(DEBUG_ASSERT_DISABLE)
    set(_debug_assert_disable DEBUG_ASSERT_DISABLE)
endif()

set(DEBUG_ASSERT_MARK_UNREACHABLE "" CACHE STRING "override of DEBUG_ASSERT_MARK_UNREACHABLE")
if(DEBUG_ASSERT_MARK_UNREACHABLE)
    set(_debug_assert_mark_unreachable "DEBUG_ASSERT_MARK_UNREACHABLE=${DEBUG_ASSERT_MARK_UNREACHABLE}")
endif()

set(DEBUG_ASSERT_ASSUME "" CACHE STRING "override of DEBUG_ASSERT_ASSUME macro")
if(DEBUG_ASSERT_ASSUME)
    set(_debug_assert_assume "DEBUG_ASSERT_ASSUME=${DEBUG_ASSERT_ASSUME}")
endif()

set(DEBUG_ASSERT_FORCE_INLINE "" CACHE STRING "override of DEBUG_ASSERT_FORCE_INLINE macro")
if(DEBUG_ASSERT_FORCE_INLINE)
    set(_debug_assert_force_inline "DEBUG_ASSERT_FORCE_INLINE=${DEBUG_ASSERT_FORCE_INLINE}")
endif()

# interface target
add_library(debug_assert INTERFACE)
target_sources(debug_assert INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/debug_assert.hpp>)
target_include_directories(debug_assert INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_include_directories(debug_assert SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)
target_compile_definitions(debug_assert INTERFACE
                                        ${_debug_assert_no_stdio}
                                        ${_debug_assert_disable}
                                        ${_debug_assert_mark_unreachable}
                                        ${_debug_assert_assume}
                                        ${_debug_assert_force_inline})

# example target
add_executable(debug_assert_example EXCLUDE_FROM_ALL example.cpp)
target_link_libraries(debug_assert_example PUBLIC debug_assert)

# Create package config files
include( CMakePackageConfigHelpers )
set(CONFIG_PACKAGE_INSTALL_DIR lib/cmake/debug_assert)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debug_assert-config.cmake "
include(\${CMAKE_CURRENT_LIST_DIR}/debug_assert-targets.cmake)
set(debug_assert_LIBRARY debug_assert)
set(debug_assert_LIBRARIES debug_assert)
")

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/debug_assert-config-version.cmake
  VERSION 1.1
  COMPATIBILITY SameMajorVersion
)


# Install target and header
install(TARGETS debug_assert 
    EXPORT debug_assert-targets
    DESTINATION lib)

install(FILES debug_assert.hpp DESTINATION include)

install( EXPORT debug_assert-targets
  DESTINATION
    ${CONFIG_PACKAGE_INSTALL_DIR}
)

install( FILES
  ${CMAKE_CURRENT_BINARY_DIR}/debug_assert-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/debug_assert-config-version.cmake
  DESTINATION
    ${CONFIG_PACKAGE_INSTALL_DIR} )
cmake_minimum_required (VERSION 3.5.1 FATAL_ERROR)
project (creature)



include(CheckCXXSourceCompiles)
find_package (Threads)

###
## Setup Compiler
###

#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")


## best practice by Jason Turner
## More Flags: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md
## cmake code from https://github.com/ChaiScript/ChaiScript/blob/develop/CMakeLists.txt

if(CMAKE_COMPILER_IS_GNUCC)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

  if(GCC_VERSION VERSION_LESS 4.9)
    set(CPP11_FLAG "-std=c++1y")
  else()
    set(CPP11_FLAG "-std=c++14")
  endif()
else()
  set(CPP11_FLAG "-std=c++14")
endif()

if(MSVC)
  add_definitions(/W4 /w14545 /w34242 /w34254 /w34287 /w44263 /w44265 /w44296 /w44311 /w44826 /we4289 /w14546 /w14547 /w14549 /w14555 /w14619 /w14905 /w14906 /w14928)

  if (MSVC_VERSION STREQUAL "1800")
    # VS2013 doesn't have magic statics
    add_definitions(/w44640)
  else()
    # enum warnings are too noisy on MSVC2013
    add_definitions(/w34062)
  endif()

  add_definitions(/bigobj)
  # Note on MSVC compiler flags.
  # The code base selective disables warnings as necessary when the compiler is complaining too much
  # about something that is perfectly valid, or there is simply no technical way around it
  # This particular warning, C4503 is in regards to the decorated names that MSVC generates internally.
  # The error did not come up until the move to C++11, but the compiler doesn't give enough information
  # to determine where the error is coming from, and the internet provides no real information for
  # how to workaround or fix the error. So I'm disabling it globally.
  add_definitions(/wd4503)
else()
  add_definitions(-Wall -Wextra -Wno-error -Wconversion -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wcast-qual -Wunused -Woverloaded-virtual -Wno-old-style-cast  -pedantic ${CPP11_FLAG})

  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Weverything -Wno-c++98-compat-pedantic  -Wno-c++98-compat -Wno-documentation -Wno-switch-enum -Wno-weak-vtables -Wno-missing-prototypes -Wno-padded -Wno-missing-noreturn -Wno-exit-time-destructors -Wno-documentation-unknown-command)
  else()
    add_definitions(-Wnoexcept)
  endif()

  if(APPLE)
    add_definitions(-Wno-sign-compare)
  endif()
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  option(USE_LIBCXX "Use clang's libcxx" TRUE)

  if(USE_LIBCXX)
    add_definitions(-stdlib=libc++)
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG} -stdlib=libc++")
  else()
    set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC)
  set(LINKER_FLAGS "${LINKER_FLAGS} ${CPP11_FLAG}")
endif()

# limitations in MinGW require us to make an optimized build
# for the sake of object sizes or something
if(MINGW OR CYGWIN)
  add_definitions(-O3)
endif()

find_package (Threads)
if(CMAKE_COMPILER_IS_GNUCC)
    execute_process(COMMAND ${CMAKE_C_COMPILER} --version OUTPUT_VARIABLE GCC_FULL_VERSION)
    if(GCC_FULL_VERSION MATCHES "4.8.1.*ubuntu")
    set(LINKER_FLAGS "${LINKER_FLAGS} -Wl,--no-as-needed -pthread")
    else()
    set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
    endif()
else()
    set(LINKER_FLAGS "${LINKER_FLAGS} -pthread")
endif()

add_definitions(-pthread)


##
# Testing Compiler
##

check_cxx_source_compiles(
"
#include <cstdint>
#include <ctime>

#include <random>

int main() {

    std::random_device rd {};
    auto value = rd();

    return 0;
}
"
HAS_CXX11_RANDOM_DEVICE
)

check_cxx_source_compiles(
"
#include <cstdint>
#include <ctime>

#include <random>

int main() {

    std::default_random_engine generator(time(0));
    std::uniform_int_distribution<unsigned int> dis;
    auto value = dis(generator);

    return 0;
}
"
HAS_CXX11_DEFAULT_RANDOM_ENGINE
)

if(NOT HAS_CXX11_RANDOM_DEVICE)
    add_definitions(-DHAS_NO_CXX11_RANDOM_DEVICE)
endif()

if(NOT HAS_CXX11_DEFAULT_RANDOM_ENGINE)
    add_definitions(-DHAS_NO_CXX11_DEFAULT_RANDOM_DEVICE)
endif()









###
## 3rd libs
###
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)

