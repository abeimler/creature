### TODO avoid file(GLOB)
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cxx ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(creature_backend STATIC ${src})
add_library(Creature::Backend ALIAS creature_backend)

set_property(TARGET creature_backend PROPERTY CXX_STANDARD 14)
set_property(TARGET creature_backend PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(creature_backend PUBLIC cxx_constexpr 
                                                cxx_aggregate_default_initializers
                                                cxx_auto_type 
                                                cxx_range_for 
                                                cxx_decltype_auto 
                                                cxx_nullptr)
target_compile_features(creature_backend PRIVATE cxx_lambdas)

target_include_directories(creature_backend PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(creature_backend PRIVATE -fno-exceptions)


# use SYSTEM to get rid of 3rd party libs warnings
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/better-enums")
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/better-enums/extra")
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/cereal/include")
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/clamp")
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/json/src")

target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/entt/src")
target_include_directories(creature_backend SYSTEM PUBLIC "${CreatureBackend_SOURCE_DIR}/lib/eventpp/src")

target_include_directories(creature_backend PUBLIC "${CreatureBackend_SOURCE_DIR}/include")

unset(src)