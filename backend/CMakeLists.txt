cmake_minimum_required (VERSION 3.3 FATAL_ERROR)

file(READ ${CMAKE_CURRENT_SOURCE_DIR}/VERSION ver)
project(CreatureBackend VERSION ${ver} LANGUAGES CXX)


###
## 3rd libs
###

## header-only
#add_subdirectory(lib/entt)
#add_subdirectory(lib/eventpp)

#add_subdirectory(lib/cereal)
#add_subdirectory(lib/json)



###
## Application Build
###
add_subdirectory(src)




###
## Test Application build
###
if(BUILD_TESTING)
  ## heady-only
  #add_subdirectory(lib/doctest)

  add_subdirectory(test)
endif()







###
## Benchmark Application build
###
if(BUILD_BENCHMARKING)
  ## heady-only
  #add_subdirectory(lib/benchpress)
  
  add_subdirectory(benchmark)
endif()


