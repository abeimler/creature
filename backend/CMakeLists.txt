cmake_minimum_required (VERSION 3.3 FATAL_ERROR)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION ver)
project(CreatureBackend VERSION ${ver} LANGUAGES CXX)


###
## 3rd libs
###

add_subdirectory(lib/entt)
add_subdirectory(lib/eventpp)

add_subdirectory(lib/cereal)
add_subdirectory(lib/json)


###
## Application Build
###
add_subdirectory(src)




###
## Test Application build
###
include(CTest)

enable_testing()
if(BUILD_TESTING)
  add_subdirectory(lib/doctest)

  add_subdirectory(test)

endif()







###
## Benchmark Application build
###
option(BUILD_BENCHMARKING "Build Benchmarks" OFF)
if(BUILD_BENCHMARKING)
  add_subdirectory(lib/benchpress)
  
  add_subdirectory(benchmark)

endif()


