#include <string>

#include "benchpress/benchpress.hpp"

#include "Application/GameApplication.h"




BENCHMARK("game application update", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto entity = entities.create();

    auto& creaturecreator = app.getCreatureEntityCreator();
    creaturecreator.create(entity);

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})


BENCHMARK("[5]      game application update with    5 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 5;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[10]     game application update with   10 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 10;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[25]     game application update with   25 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 25;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[50]     game application update with   50 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 50;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[100]    game application update with  100 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 100;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[200]    game application update with  200 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 200;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[500]   game application update with   500 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 500;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[1000]  game application update with  1000 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 1000;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[2000]  game application update with  2000 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 2000;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[5000]  game application update with  5000 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 5000;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[10000] game application update with 10000 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 10000;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})

BENCHMARK("[20000] game application update with 20000 entitys", [](benchpress::context* ctx) {
    game::GameApplication app;
    gamesystem::TimeDelta fakeDelta = 1.0 / 60;

    auto& entities = app.getEntityManager();
    auto& creaturecreator = app.getCreatureEntityCreator();

    for(size_t i = 0;i < 20000;i++) {
        auto entity = entities.create();
        creaturecreator.create(entity);
    }

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i) {
        app.update(fakeDelta);
    }
})