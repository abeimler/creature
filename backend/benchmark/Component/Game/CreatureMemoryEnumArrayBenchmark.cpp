#include "benchpress/benchpress.hpp"

#include <algorithm>
#include <array>
#include <vector>

#include "basic.h"
#include "enum_array.h"

#include "Component/Game/CreatureMemory.h"

class CreatureMemoryDeepMemoryEnumArrayBenchmark {
    public:
    static void init_enum_array_CreatureMemoryDeepMemory(
        earr::enum_array<gamecomp::CreatureActivity,
                         gamecomp::CreatureMemoryDeepMemory>& deep_memory) {
        auto enum_creatureactivity = earr::Enum<gamecomp::CreatureActivity>();

        for (auto index : enum_creatureactivity) {
            gamecomp::CreatureMemoryDeepMemory memory;
            memory.activity = index;
            earr::enum_array_set(deep_memory, index, memory);
        }
    }

    static earr::enum_array<gamecomp::CreatureActivity,
                            gamecomp::CreatureMemoryDeepMemory>
    make_enum_array_CreatureMemoryDeepMemory() {
        earr::enum_array<gamecomp::CreatureActivity,
                         gamecomp::CreatureMemoryDeepMemory>
            deep_memory;
        auto enum_creatureactivity = earr::Enum<gamecomp::CreatureActivity>();

        for (auto index : enum_creatureactivity) {
            gamecomp::CreatureMemoryDeepMemory memory;
            memory.activity = index;
            earr::enum_array_set(deep_memory, index, memory);
        }

        return deep_memory;
    }
};



BENCHMARK("gamecomp::CreatureMemory.deep_memory as enum_array",
          [](benchpress::context* ctx) {
              // not working, why ?? compile error: macro "BENCHMARK" passed 3
              // arguments, but takes just 2
              /*
              earr::enum_array<gamecomp::CreatureActivity,
              gamecomp::CreatureMemoryDeepMemory> deep_memory;

              CreatureMemoryDeepMemoryEnumArrayBenchmark::init_enum_array_CreatureMemoryDeepMemory(deep_memory);
              */
              auto deep_memory = CreatureMemoryDeepMemoryEnumArrayBenchmark::
                  make_enum_array_CreatureMemoryDeepMemory();

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