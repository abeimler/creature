
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

set_property(TARGET ${PROJECT_NAME}_makedata PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME}_makedata PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME}_makedata PRIVATE creature_backend)

target_include_directories(${PROJECT_NAME}_makedata PUBLIC ${TOOLS_MAKEDATA_LIB_PATH}/cxxopts/src)

target_include_directories(${PROJECT_NAME}_makedata PRIVATE ${TOOLS_MAKEDATA_INCLUDE_PATH})
target_include_directories(${PROJECT_NAME}_makedata PRIVATE ${CREATURE_BACKEND_INCLUDE_PATH})

target_compile_options(${PROJECT_NAME}_makedata PRIVATE -fexceptions)



###
## Tools
###


# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)

  add_custom_target(clang-format_makedata
      COMMAND find ${TOOLS_MAKEDATA_SRC_PATH} -name '*.cpp' -exec 
          ${CLANG_FORMAT}
          -style=file
          -i
          {} +
        || find ${TOOLS_MAKEDATA_INCLUDE_PATH} -name '*.h' -exec 
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

  add_custom_target(clang-tidy_makedata
    COMMAND find ${TOOLS_MAKEDATA_SRC_PATH} -name '*.cpp' -exec 
      ${CLANG_TIDY} 
        -p ${CMAKE_CURRENT_BINARY_DIR} 
        -config='' 
        -fix
        {} +

    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )

endif()