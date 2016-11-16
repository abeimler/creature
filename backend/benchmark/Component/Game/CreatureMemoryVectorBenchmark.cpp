#include "benchpress/benchpress.hpp"

#include <array>
#include <vector>
#include <algorithm>

#include "basic.h"
#include "enum_array.h"

#include "Component/Game/CreatureMemory.h"

class CreatureMemoryDeepMemoryVectorBenchmark {
    public:

    static void init_vector_CreatureMemoryDeepMemory(
        std::vector<gamecomp::CreatureMemoryDeepMemory>& deep_memory) {
        auto enum_creatureactivity = earr::Enum<gamecomp::CreatureActivity>();

        deep_memory.reserve(enum_creatureactivity.count);
        for (auto index : enum_creatureactivity) {
            gamecomp::CreatureMemoryDeepMemory memory;
            memory.activity = index;
            deep_memory.push_back(memory);
        }
    }

};





BENCHMARK("gamecomp::CreatureMemory.deep_memory as vector",
          [](benchpress::context* ctx) {
              std::vector<gamecomp::CreatureMemoryDeepMemory> deep_memory;

              CreatureMemoryDeepMemoryVectorBenchmark::init_vector_CreatureMemoryDeepMemory(deep_memory);

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

