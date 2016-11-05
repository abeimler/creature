#include <string>
#include <vector>
#include <thread>
#include <memory>

#include "benchpress/benchpress.hpp"

#include "entityx/entityx.hh"

class EntityXBenchmark {
    public:

    struct PositionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct DirectionComponent {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct ComflabulationComponent {
        float thingy = 0.0;
        int dingy = 0;
        bool mingy = false;
        std::string stringy;
    };


    // Convenience types for our entity system.
    using GameComponents = entityx::Components<
        PositionComponent, DirectionComponent, ComflabulationComponent
    >;

    static constexpr size_t INITIAL_CAPACITY = 16384; // bignumber to avoid alloc error, benchmark a lot of enteties
    using EntityManager = entityx::EntityX<GameComponents, entityx::ColumnStorage<GameComponents, INITIAL_CAPACITY>>;

    template <typename C>
    using Component = EntityManager::Component<C>;

    using Entity = EntityManager::Entity;




    class System {
        public:
        // virtual dtor and the rule of 6
        System() = default;
        virtual ~System() = default;
        System(const System&) = default;
        System& operator=(const System&) = default;
        System(System&&) = default;
        System& operator=(System&&) = default;

        virtual void update(EntityManager& es, double dt) = 0;
    };


    class MovementSystem : public System {
        public:
        MovementSystem() = default;

        void update(EntityManager& es, double dt) override {
            Component<PositionComponent> position;
            Component<DirectionComponent> direction;

            for (Entity entity : es.entities_with_components<PositionComponent, DirectionComponent>(position, direction)) {
                position->x += direction->x * dt;
                position->y += direction->y * dt;
            }
        }
    };

    class ComflabSystem : public System {
        public:
        ComflabSystem() = default;

        void update(EntityManager& es, double dt) override {
            Component<ComflabulationComponent> comflab;

            for (Entity entity : es.entities_with_components<ComflabulationComponent>(comflab)) {
                comflab->thingy *= 1.000001f;
                comflab->mingy = !comflab->mingy;
                comflab->dingy++;
                //comflab.stringy = std::to_string(comflab.dingy);
            }
        }
    };

    class Application {
        public:
        explicit Application() {
            this->systems_.emplace_back(std::make_unique<MovementSystem>());
            this->systems_.emplace_back(std::make_unique<ComflabSystem>());
        }

        void update(double dt) {
            for (auto& system : this->systems_) {
                system->update(this->entities_, dt);
            }
        }

        EntityManager& getEntityManager() { return this->entities_; }
        const EntityManager& getEntityManager() const { return this->entities_; }

        private:
        EntityManager entities_;
        std::vector<std::unique_ptr<System>> systems_;
    };

    static constexpr double fakeDeltaTime = 1.0 / 60;
};



BENCHMARK("entityx create destroy entity with components", [](benchpress::context* ctx) {
    EntityXBenchmark::EntityManager entities;

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        auto entity = entities.create();

        entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();
		entity.assign<EntityXBenchmark::ComflabulationComponent>();

        entities.destroy(entity.id());
    }
})



BENCHMARK("entityx    25 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 25; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})

BENCHMARK("entityx    50 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 50; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})

BENCHMARK("entityx   100 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 100; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})

BENCHMARK("entityx   200 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 200; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})


BENCHMARK("entityx   400 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 400; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})


BENCHMARK("entityx   800 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 800; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})


BENCHMARK("entityx  1600 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 1600; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})



BENCHMARK("entityx  3200 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 3200; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})


BENCHMARK("entityx  5000 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 5000; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})


BENCHMARK("entityx 10000 entities component systems update", [](benchpress::context* ctx) {
    EntityXBenchmark::Application app;
    auto& entities = app.getEntityManager();

    for (size_t i = 0; i < 10000; i++) {
		auto entity = entities.create();

		entity.assign<EntityXBenchmark::PositionComponent>();
		entity.assign<EntityXBenchmark::DirectionComponent>();

		if (i % 2) {
			entity.assign<EntityXBenchmark::ComflabulationComponent>();
		}
	}

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(EntityXBenchmark::fakeDeltaTime);
    }
})