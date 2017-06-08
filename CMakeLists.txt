cmake_minimum_required (VERSION 3.3 FATAL_ERROR)

file(READ VERSION ver)
project (Creature VERSION ${ver})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Creature_BINARY_DIR}")

###
## sub dirs
###
add_subdirectory(backend)

