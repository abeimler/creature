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



include(${CMAKE_CURRENT_SOURCE_DIR}/tools.makedata.cmake)


###
## Tools
###


# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)

  add_custom_target(clang-format
      DEPENDS clang-format_backend
        clang-format_backend_test
        clang-format_backend_benchmark
        clang-format_makedata 

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)

  add_custom_target(clang-tidy
    DEPENDS clang-tidy_backend
      clang-tidy_backend_test
      clang-tidy_backend_benchmark
      clang-tidy_makedata

    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

endif()