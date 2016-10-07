cmake_minimum_required (VERSION 2.6)
project (mainapp C CXX)


###
## Setup Compiler
###

#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(warnings "-Wall -Wextra")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Wno-missing-braces -Wmissing-field-initializers")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()





###
## Source/Header Files
###
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB_RECURSE SRC ${SRC_PATH}/*.cpp ${SRC_PATH}/*.cxx ${SRC_PATH}/*.cc)
file(GLOB_RECURSE HEADERS ${SRC_PATH}/*.h ${SRC_PATH}/*.hpp ${SRC_PATH}/*.hxx)

file(GLOB_RECURSE TEST_SRC ${TEST_PATH}/*.cpp ${TEST_PATH}/*.cxx ${TEST_PATH}/*.cc)
file(GLOB_RECURSE TEST_HEADERS ${TEST_PATH}/*.h ${TEST_PATH}/*.hpp ${TEST_PATH}/*.hxx)

include_directories(${INCLUDE_PATH})
include_directories(${SRC_PATH})


###
## 3rd libs
###
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(ENTITYX_BUILD_SHARED 0)
add_subdirectory(${LIB_PATH}/entityx)




###
## Application Build
###
add_library(${PROJECT_NAME} STATIC ${SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME} c++abi)
endif()

target_link_libraries(${PROJECT_NAME} entityx)



###
## Test Application build
###

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME}_test c++abi)
endif()

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${TEST_PATH})

enable_testing ()
add_test (NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)