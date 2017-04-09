#include "benchpress/benchpress.hpp"

#include "Entity/Game/CreatureEntityCreator.h"

namespace creatureentitycreator_benchmark {

BENCHMARK("CreatureEntityCreator create entity assign destory",
          [](benchpress::context* ctx) {
              gameentity::EntityManager entities;
              gameentity::CreatureEntityCreator creator;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                  auto entity = entities.create();
                  creator.create(entity);
                  entities.destroy(entity.id());
              }
          })

} // namespace creatureentitycreator_benchmark