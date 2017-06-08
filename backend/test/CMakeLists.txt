add_library(creature_backend_test_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/mainTest.cpp)
add_library(Creature::Backend.Test::Main ALIAS creature_backend_test_main)


set_property(TARGET creature_backend_test_main PROPERTY CXX_STANDARD 14)
set_property(TARGET creature_backend_test_main PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(creature_backend_test_main PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr)
target_compile_features(creature_backend_test_main PRIVATE cxx_lambdas)


target_include_directories(creature_backend_test_main PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(creature_backend_test_main PRIVATE -fexceptions)
target_link_libraries (creature_backend_test_main PRIVATE ${CMAKE_THREAD_LIBS_INIT})


target_include_directories(creature_backend_test_main SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/doctest/doctest")

target_link_libraries(creature_backend_test_main PUBLIC creature_backend)
#target_link_libraries(creature_backend_test_main PUBLIC doctest)



add_custom_target(
    creature_backend_test_build
    # Workaround for printing the COMMENT, it does not work without a NOOP
    # COMMAND.
    COMMAND ${CMAKE_COMMAND} -E echo
    COMMENT "Building tests..."
    VERBATIM
)

### TODO avoid file(GLOB)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)
list(REMOVE_ITEM src ${CMAKE_CURRENT_SOURCE_DIR}/mainTest.cpp) # already use it in Test.Main

foreach(src_file ${src})

    get_filename_component(src_file_base_name "${src_file}" NAME)
    string(REPLACE ".cpp" "" src_file_base_name ${src_file_base_name})
    string(REPLACE ".cxx" "" src_file_base_name ${src_file_base_name})
    string(REPLACE ".cc" "" src_file_base_name ${src_file_base_name})
    set(test_name "Creature::Backend.${src_file_base_name}.Test")
    set(test_command "creature_backend_${src_file_base_name}_test")



    add_executable(${test_command} ${src_file})

    set_property(TARGET ${test_command} PROPERTY CXX_STANDARD 14)
    set_property(TARGET ${test_command} PROPERTY CXX_STANDARD_REQUIRED ON)

    target_link_libraries (${test_command} PRIVATE Creature::Backend.Test::Main)

    target_compile_options(${test_command} PRIVATE -fexceptions)
    target_link_libraries (${test_command} PRIVATE ${CMAKE_THREAD_LIBS_INIT})


    add_test(NAME ${test_name} COMMAND ${test_command})
    add_dependencies(creature_backend_test_build ${test_command})
endforeach()

# The "check" target is used to build AND run all test executables.
add_custom_target(
    creature_backend_test
    # Either invoke the test(s) indirectly via "CTest" (commented) or directly.
    #   COMMAND ${CMAKE_CTEST_COMMAND}
    COMMAND ctest ARGS --output-on-failure
    COMMENT "Building and running test..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM
)
add_dependencies(creature_backend_test creature_backend_test_build)


unset(src)