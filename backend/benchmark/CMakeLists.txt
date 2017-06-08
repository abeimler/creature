### TODO avoid file(GLOB)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(creature_backend_benchmark STATIC ${src})
add_library(Creature::Backend.Benchmark ALIAS creature_backend_benchmark)

set_property(TARGET creature_backend_benchmark PROPERTY CXX_STANDARD 14)
set_property(TARGET creature_backend_benchmark PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(creature_backend_benchmark PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr)
target_compile_features(creature_backend_benchmark PRIVATE cxx_lambdas cxx_raw_string_literals cxx_user_literals)


target_include_directories(creature_backend_benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(creature_backend_benchmark PRIVATE -fexceptions)
target_link_libraries (creature_backend_benchmark PRIVATE ${CMAKE_THREAD_LIBS_INIT})


target_include_directories(creature_backend_benchmark SYSTEM PUBLIC "${Creature::Backend_SOURCE_DIR}/lib/benchpress/src")

target_link_libraries(creature_backend_benchmark PUBLIC creature_backend)
target_link_libraries(creature_backend_benchmark PUBLIC benchpress)

unset(src)