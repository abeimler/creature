cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (creature_backend VERSION 0.1.0 LANGUAGES CXX)

include(CheckCXXSourceCompiles)

###
## Setup Compiler
###

#set(CMAKE_C_COMPILER "/usr/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    

## best practice by Jason Turner
## More Flags: https://github.com/lefticus/cppbestpractices/blob/master/02-Use_the_Tools_Available.md

if (CMAKE_COMPILER_IS_GNUCXX)
    set(warnings "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(warnings "${warnings} -Weverything")
    endif()
    set(warnings "${warnings} -pedantic")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /W44640 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

find_package (Threads)

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
## Source/Header Files
###
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(BENCHMARK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/benchmark)

file(GLOB_RECURSE SRC ${SRC_PATH}/*.cpp ${SRC_PATH}/*.cxx ${SRC_PATH}/*.cc)
file(GLOB_RECURSE HEADERS ${SRC_PATH}/*.h ${SRC_PATH}/*.hpp ${SRC_PATH}/*.hxx)

file(GLOB_RECURSE TEST_SRC ${TEST_PATH}/*.cpp ${TEST_PATH}/*.cxx ${TEST_PATH}/*.cc)
file(GLOB_RECURSE TEST_HEADERS ${TEST_PATH}/*.h ${TEST_PATH}/*.hpp ${TEST_PATH}/*.hxx)

file(GLOB_RECURSE BENCHMARK_SRC ${BENCHMARK_PATH}/*.cpp ${BENCHMARK_PATH}/*.cxx ${BENCHMARK_PATH}/*.cc)
file(GLOB_RECURSE BENCHMARK_HEADERS ${BENCHMARK_PATH}/*.h ${BENCHMARK_PATH}/*.hpp ${BENCHMARK_PATH}/*.hxx)



###
## 3rd libs
###
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(ENTITYX_BUILD_SHARED 0)
add_subdirectory(${LIB_PATH}/entityx)

add_subdirectory(${LIB_PATH}/benchpress)
add_subdirectory(${LIB_PATH}/doctest)

add_subdirectory(${LIB_PATH}/cereal)
add_subdirectory(${LIB_PATH}/GSL)
add_subdirectory(${LIB_PATH}/json)

# no cmake support
#add_subdirectory(${LIB_PATH}/better-enums)
#add_subdirectory(${LIB_PATH}/clamp)


###
## Application Build
###
add_library(${PROJECT_NAME} STATIC ${SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME} c++abi)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_lambdas)


target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/entityx)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/better-enums)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/better-enums/extra)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/cereal/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/clamp)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/GSL)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_PATH}/json/src)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_PATH})

target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)


###
## Test Application build
###

add_executable(${PROJECT_NAME}_test ${TEST_SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME}_test c++abi)
endif()

set_property(TARGET ${PROJECT_NAME}_test PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_test PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_test PRIVATE ${TEST_PATH})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${LIB_PATH}/doctest/doctest)

target_compile_options(${PROJECT_NAME}_test PRIVATE -fexceptions)

enable_testing ()
add_test (NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)


###
## Benchmark Application build
###
add_executable(${PROJECT_NAME}_benchmark ${BENCHMARK_SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME}_benchmark c++abi)
endif()

set_property(TARGET ${PROJECT_NAME}_benchmark PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_benchmark PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_benchmark PRIVATE ${BENCHMARK_PATH})
target_include_directories(${PROJECT_NAME}_benchmark PRIVATE ${LIB_PATH}/benchpress/src)

target_compile_options(${PROJECT_NAME}_benchmark PRIVATE -fexceptions)

target_link_libraries (${PROJECT_NAME}_benchmark PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(${PROJECT_NAME}_benchmark PRIVATE -pthread)

###
## Tools
###


# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT}
    -i
    -style=file
    ${SRC} ${TEST_SRC}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND ${CLANG_TIDY}
    ${SRC} ${TEST_SRC}
    -config=''
    --
    ${CMAKE_CXX_FLAGS}
    ${INCLUDE_DIRECTORIES}
    )
endif()
