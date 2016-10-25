#include "benchpress/benchpress.hpp"

#include <array>
#include <vector>

#include "basic.h"
#include "enum_array.h"

#include "Component/Game/CreatureMemory.h"

void init_enum_array_CreatureMemoryDeepMemory(
    earr::enum_array<gamecomp::CreatureActivity,
                     gamecomp::CreatureMemoryDeepMemory>& deep_memory) {
    auto enum_creatureactivity = earr::Enum<gamecomp::CreatureActivity>();

    for (auto index : enum_creatureactivity) {
        gamecomp::CreatureMemoryDeepMemory memory;
        memory.activity = index;
        earr::enum_array_set(deep_memory, index, memory);
    }
}

void init_vector_CreatureMemoryDeepMemory(
    std::vector<gamecomp::CreatureMemoryDeepMemory>& deep_memory) {
    auto enum_creatureactivity = earr::Enum<gamecomp::CreatureActivity>();

    deep_memory.reserve(enum_creatureactivity.count);
    for (auto index : enum_creatureactivity) {
        gamecomp::CreatureMemoryDeepMemory memory;
        memory.activity = index;
        deep_memory.push_back(memory);
    }
}


/*
BENCHMARK("gamecomp::CreatureMemory.deep_memory as enum_array",
          [](benchpress::context* ctx) {
              earr::enum_array<gamecomp::CreatureActivity,
                               gamecomp::CreatureMemoryDeepMemory>
                  deep_memory;

              init_enum_array_CreatureMemoryDeepMemory(deep_memory);

              gamecomp::CreatureActivity find_key =
                  +gamecomp::CreatureActivity::MakeDigestionHeapToilet;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto find_func = [find_key](
                      const gamecomp::CreatureMemoryDeepMemory& memory) {
                      return memory.activity == find_key;
                  };

                  auto it = std::find_if(std::begin(deep_memory),
                                         std::end(deep_memory), find_func);

                  benchpress::escape(&it);
              }
          })
*/

BENCHMARK("gamecomp::CreatureMemory.deep_memory as vector",
          [](benchpress::context* ctx) {
              std::vector<gamecomp::CreatureMemoryDeepMemory> deep_memory;

              init_vector_CreatureMemoryDeepMemory(deep_memory);

              gamecomp::CreatureActivity find_key =
                  +gamecomp::CreatureActivity::MakeDigestionHeapToilet;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto find_func = [find_key](
                      const gamecomp::CreatureMemoryDeepMemory& memory) {
                      return memory.activity == find_key;
                  };

                  auto it = std::find_if(std::begin(deep_memory),
                                         std::end(deep_memory), find_func);

                  benchpress::escape(&it);
              }
          })
