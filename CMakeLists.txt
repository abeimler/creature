cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
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

if (CMAKE_COMPILER_IS_GNUCXX)
    set(warnings "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Woverloaded-virtual")
    # set(warnings "${warnings} -Weffc++")
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
## 3rd libs
###
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend)




###
## Application Build
###

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tools/makedata)

set(TOOLS_MAKEDATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools/makedata)
set(TOOLS_MAKEDATA_LIB_PATH ${TOOLS_MAKEDATA_DIR}/lib)
set(TOOLS_MAKEDATA_SRC_PATH ${TOOLS_MAKEDATA_DIR}/src)
set(TOOLS_MAKEDATA_INCLUDE_PATH ${TOOLS_MAKEDATA_DIR}/include)




file(GLOB_RECURSE TOOLS_MAKEDATA_SRC ${TOOLS_MAKEDATA_SRC_PATH}/*.cpp ${TOOLS_MAKEDATA_SRC_PATH}/*.cxx ${TOOLS_MAKEDATA_SRC_PATH}/*.cc)
file(GLOB_RECURSE TOOLS_MAKEDATA_HEADERS ${TOOLS_MAKEDATA_SRC_PATH}/*.h ${TOOLS_MAKEDATA_SRC_PATH}/*.hpp ${TOOLS_MAKEDATA_SRC_PATH}/*.hxx)

add_executable(${PROJECT_NAME}_makedata ${TOOLS_MAKEDATA_SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME}_makedata c++abi)
endif()

set_property(TARGET ${PROJECT_NAME}_makedata PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_makedata PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_makedata PRIVATE creature_backend)

target_include_directories(${PROJECT_NAME}_makedata PUBLIC ${TOOLS_MAKEDATA_LIB_PATH}/cxxopts/src)

target_include_directories(${PROJECT_NAME}_makedata PRIVATE ${TOOLS_MAKEDATA_INCLUDE_PATH})
target_include_directories(${PROJECT_NAME}_makedata PRIVATE ${CREATURE_BACKEND_INCLUDE_PATH})

target_compile_options(${PROJECT_NAME}_makedata PRIVATE -fexceptions)

target_link_libraries (${PROJECT_NAME}_makedata PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(${PROJECT_NAME}_makedata PRIVATE -pthread)

