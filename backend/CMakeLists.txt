cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (creature_backend VERSION 0.1.0 LANGUAGES CXX)

###
## Source/Header Files
###
set(CREATURE_BACKEND_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CREATURE_BACKEND_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CREATURE_BACKEND_TEST_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(CREATURE_BACKEND_BENCHMARK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/benchmark)

file(GLOB_RECURSE CREATURE_BACKEND_SRC ${CREATURE_BACKEND_SRC_PATH}/*.cpp ${CREATURE_BACKEND_SRC_PATH}/*.cxx ${CREATURE_BACKEND_SRC_PATH}/*.cc)
file(GLOB_RECURSE CREATURE_BACKEND_HEADERS ${CREATURE_BACKEND_INCLUDE_PATH}/*.h ${CREATURE_BACKEND_INCLUDE_PATH}/*.hpp ${CREATURE_BACKEND_INCLUDE_PATH}/*.hxx)

file(GLOB_RECURSE CREATURE_BACKEND_TEST_SRC ${CREATURE_BACKEND_TEST_PATH}/*.cpp ${CREATURE_BACKEND_TEST_PATH}/*.cxx ${CREATURE_BACKEND_TEST_PATH}/*.cc)
file(GLOB_RECURSE CREATURE_BACKEND_TEST_HEADERS ${CREATURE_BACKEND_TEST_PATH}/*.h ${CREATURE_BACKEND_TEST_PATH}/*.hpp ${CREATURE_BACKEND_TEST_PATH}/*.hxx)
set(CREATURE_BACKEND_TEST_SRC_MAIN_CPP ${CREATURE_BACKEND_TEST_PATH}/mainTest.cpp)
list(REMOVE_ITEM CREATURE_BACKEND_TEST_SRC "${CREATURE_BACKEND_TEST_SRC_MAIN_CPP}")

file(GLOB_RECURSE CREATURE_BACKEND_BENCHMARK_SRC ${CREATURE_BACKEND_BENCHMARK_PATH}/*.cpp ${CREATURE_BACKEND_BENCHMARK_PATH}/*.cxx ${CREATURE_BACKEND_BENCHMARK_PATH}/*.cc)
file(GLOB_RECURSE CREATURE_BACKEND_BENCHMARK_HEADERS ${CREATURE_BACKEND_BENCHMARK_PATH}/*.h ${CREATURE_BACKEND_BENCHMARK_PATH}/*.hpp ${CREATURE_BACKEND_BENCHMARK_PATH}/*.hxx)




set(CREATURE_BACKEND_SRC_PATH ${CREATURE_BACKEND_SRC_PATH} PARENT_SCOPE)
set(CREATURE_BACKEND_INCLUDE_PATH ${CREATURE_BACKEND_INCLUDE_PATH} PARENT_SCOPE)
set(CREATURE_BACKEND_TEST_PATH ${CREATURE_BACKEND_TEST_PATH} PARENT_SCOPE)
set(CREATURE_BACKEND_BENCHMARK_PATH ${CREATURE_BACKEND_BENCHMARK_PATH} PARENT_SCOPE)

set(CREATURE_BACKEND_SRC ${CREATURE_BACKEND_SRC} PARENT_SCOPE)
set(CREATURE_BACKEND_HEADERS ${CREATURE_BACKEND_HEADERS} PARENT_SCOPE)

set(CREATURE_BACKEND_SRC ${CREATURE_BACKEND_SRC} PARENT_SCOPE)
set(CREATURE_BACKEND_HEADERS ${CREATURE_BACKEND_HEADERS} PARENT_SCOPE)
set(CREATURE_BACKEND_TEST_SRC_MAIN_CPP ${CREATURE_BACKEND_TEST_SRC_MAIN_CPP} PARENT_SCOPE)

set(CREATURE_BACKEND_TEST_SRC ${CREATURE_BACKEND_TEST_SRC} PARENT_SCOPE)
set(CREATURE_BACKEND_TEST_HEADERS ${CREATURE_BACKEND_TEST_HEADERS} PARENT_SCOPE)

set(CREATURE_BACKEND_BENCHMARK_SRC ${CREATURE_BACKEND_BENCHMARK_SRC} PARENT_SCOPE)
set(CREATURE_BACKEND_BENCHMARK_HEADERS ${CREATURE_BACKEND_BENCHMARK_HEADERS} PARENT_SCOPE)




###
## 3rd libs
###
set(CREATURE_BACKEND_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/entityx)
add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/eventpp)

add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/benchpress)
add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/doctest)

add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/cereal)
add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/GSL)
add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/json)

add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/type_safe)

# no cmake support
#add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/better-enums)
#add_subdirectory(${CREATURE_BACKEND_LIB_PATH}/clamp)


###
## Application Build
###
add_library(${PROJECT_NAME} STATIC ${CREATURE_BACKEND_SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_lambdas)

# use SYSTEM to get rid of 3rd party libs warnings
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/entityx)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/eventpp/src)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/better-enums)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/better-enums/extra)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/cereal/include)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/clamp)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/GSL)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/json/src)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/type_safe/include)
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${CREATURE_BACKEND_LIB_PATH}/type_safe/external/debug_assert)

target_include_directories(${PROJECT_NAME} PUBLIC ${CREATURE_BACKEND_INCLUDE_PATH})
target_include_directories(${PROJECT_NAME} PRIVATE ${CREATURE_BACKEND_SRC_PATH})

target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)


###
## Test Application build
###

add_library(${PROJECT_NAME}_test_main STATIC ${CREATURE_BACKEND_TEST_SRC_MAIN_CPP})
set_property(TARGET ${PROJECT_NAME}_test_main PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_test_main PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_test_main PRIVATE ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_test_main SYSTEM PRIVATE ${CREATURE_BACKEND_LIB_PATH}/doctest/doctest)
target_include_directories(${PROJECT_NAME}_test_main PRIVATE ${CREATURE_BACKEND_TEST_PATH})

target_compile_options(${PROJECT_NAME}_test_main PRIVATE -fexceptions)
target_link_libraries (${PROJECT_NAME}_test_main PRIVATE ${CMAKE_THREAD_LIBS_INIT})


enable_testing ()
add_custom_target(${PROJECT_NAME}_test)
foreach(CREATURE_BACKEND_TEST_SRC_FILE ${CREATURE_BACKEND_TEST_SRC})

  get_filename_component(CREATURE_BACKEND_TEST_NAME_BASE "${CREATURE_BACKEND_TEST_SRC_FILE}" NAME)
  string(REPLACE ".cpp" "" CREATURE_BACKEND_TEST_NAME_BASE ${CREATURE_BACKEND_TEST_NAME_BASE})
  string(REPLACE ".cxx" "" CREATURE_BACKEND_TEST_NAME_BASE ${CREATURE_BACKEND_TEST_NAME_BASE})
  string(REPLACE ".cc" "" CREATURE_BACKEND_TEST_NAME_BASE ${CREATURE_BACKEND_TEST_NAME_BASE})
  set(CREATURE_BACKEND_TEST_NAME "${PROJECT_NAME}_${CREATURE_BACKEND_TEST_NAME_BASE}_test")



  add_executable(${CREATURE_BACKEND_TEST_NAME} ${CREATURE_BACKEND_TEST_SRC_FILE})
  set_property(TARGET ${CREATURE_BACKEND_TEST_NAME} PROPERTY CXX_STANDARD 14)
  set_property(TARGET ${CREATURE_BACKEND_TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

  target_link_libraries(${CREATURE_BACKEND_TEST_NAME} PRIVATE ${PROJECT_NAME})

  target_include_directories(${CREATURE_BACKEND_TEST_NAME} SYSTEM PRIVATE ${CREATURE_BACKEND_LIB_PATH}/doctest/doctest)
  target_include_directories(${CREATURE_BACKEND_TEST_NAME} PRIVATE ${CREATURE_BACKEND_TEST_PATH})

  target_compile_options(${CREATURE_BACKEND_TEST_NAME} PRIVATE -fexceptions)
  target_link_libraries (${CREATURE_BACKEND_TEST_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})
  target_link_libraries (${CREATURE_BACKEND_TEST_NAME} PRIVATE ${PROJECT_NAME}_test_main)


  add_test (NAME ${CREATURE_BACKEND_TEST_NAME} COMMAND ${CREATURE_BACKEND_TEST_NAME})
  add_dependencies(${PROJECT_NAME}_test ${CREATURE_BACKEND_TEST_NAME})
endforeach()








###
## Benchmark Application build
###
add_executable(${PROJECT_NAME}_benchmark ${CREATURE_BACKEND_BENCHMARK_SRC})
if((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") AND (UNIX))
    target_link_libraries(${PROJECT_NAME}_benchmark c++abi)
endif()

set_property(TARGET ${PROJECT_NAME}_benchmark PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_benchmark PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}_benchmark PRIVATE ${CREATURE_BACKEND_LIB_PATH}/benchpress/src)
target_include_directories(${PROJECT_NAME}_benchmark SYSTEM PRIVATE ${CREATURE_BACKEND_BENCHMARK_PATH})

target_compile_options(${PROJECT_NAME}_benchmark PRIVATE -fexceptions)
target_link_libraries (${PROJECT_NAME}_benchmark PRIVATE ${CMAKE_THREAD_LIBS_INIT})




###
## Tools
###


# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)

  add_custom_target(
    clang-format_backend
      COMMAND find ${CREATURE_BACKEND_SRC_PATH} -name '*.cpp' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +
        || find ${CREATURE_BACKEND_INCLUDE_PATH} -name '*.h' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

  add_custom_target(
    clang-format_backend_test
      COMMAND find ${CREATURE_BACKEND_TEST_PATH} -name '*.cpp' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +
        || find ${CREATURE_BACKEND_TEST_PATH} -name '*.h' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

  add_custom_target(
    clang-format_backend_benchmark
      COMMAND find ${CREATURE_BACKEND_BENCHMARK_PATH} -name '*.cpp' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +
        || find ${CREATURE_BACKEND_BENCHMARK_PATH} -name '*.h' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)

  add_custom_target(clang-tidy_backend
    COMMAND find ${CREATURE_BACKEND_SRC_PATH} -name '*.cpp' -exec 
      ${CLANG_TIDY} 
        -p ${CMAKE_CURRENT_BINARY_DIR} 
        -config='' 
        -fix
        {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(clang-tidy_backend_test
    COMMAND find ${CREATURE_BACKEND_TEST_PATH} -name '*.cpp' -exec 
      ${CLANG_TIDY} 
        -p ${CMAKE_CURRENT_BINARY_DIR} 
        -config='' 
        -fix
        {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

  add_custom_target(clang-tidy_backend_benchmark
    COMMAND find ${CREATURE_BACKEND_BENCHMARK_PATH} -name '*.cpp' -exec 
      ${CLANG_TIDY} 
        -p ${CMAKE_CURRENT_BINARY_DIR} 
        -config='' 
        -fix
        {} +

      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

endif()
