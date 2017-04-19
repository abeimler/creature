#include "benchpress/benchpress.hpp"

#include "Entity/Game/CreatureEntityCreator.h"

namespace creatureentitycreator_benchmark {

BENCHMARK("CreatureEntityCreator create creature entity",
          [](benchpress::context* ctx) {
              gameentity::EntityManager entities;
              gameentity::CreatureEntityCreator creator;

              ctx->reset_timer();
              for (size_t i = 0; i < ctx->num_iterations(); ++i) {
                auto entity = entities.create();

                ctx->start_timer();
                creator.create(entities, entity);
                ctx->stop_timer();

                entities.destroy(entity);
              }
          })

} // namespace creatureentitycreator_benchmark