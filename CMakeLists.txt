cmake_minimum_required (VERSION 3.3 FATAL_ERROR)

file(READ VERSION ver)
project (Creature VERSION ${ver})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Creature_BINARY_DIR}")

include(CTest)

enable_testing()
option(BUILD_BENCHMARKING "Build Benchmarks" OFF)

###
## sub dirs
###
add_subdirectory(backend)

