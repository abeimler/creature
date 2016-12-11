#include <thread>

#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureGrowingIncrementListener.h"
#include "System/Game/CreatureGrowingSystem.h"
#include "System/Game/CreatureProgressTimerSystem.h"


class CreatureGrowingSystemApplication : public gamesystem::Application {
    private:
    public:
    std::shared_ptr<gamesystem::CreatureProgressTimerSystem>
        creatureProgressTimerSystem;
    std::shared_ptr<gamesystem::CreatureGrowingIncrementListener>
        creatureGrowingIncrementListener;
    std::shared_ptr<gamesystem::CreatureGrowingSystem>
        creatureGrowingSystem;

    CreatureGrowingSystemApplication() {
        this->creatureProgressTimerSystem =
            std::make_shared<gamesystem::CreatureProgressTimerSystem>();
        this->creatureGrowingIncrementListener =
            std::make_shared<gamesystem::CreatureGrowingIncrementListener>();
        this->creatureGrowingSystem =
            std::make_shared<gamesystem::CreatureGrowingSystem>();

        this->addSystem(this->creatureProgressTimerSystem);
        this->addListener(this->creatureGrowingIncrementListener);
        this->addSystem(this->creatureGrowingSystem);
    }



    void init_Entity_NotStartedGrowingTimer(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& growing_timer = earr::enum_array_at(timers->increment, 
            +gamecomp::CreatureProgressTimerIncrement::Growing);

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(growing_timer.base, time, 1.0f);
    }

    void init_Entity_withFullGrowingTimer(gameentity::Entity entity) {
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& growing_timer = earr::enum_array_at(timers->increment, 
            +gamecomp::CreatureProgressTimerIncrement::Growing);

        progresstimer_util.start(growing_timer.base);

        growing_timer.base.value = 100.0f;
        growing_timer.base.isfull = true;
    }

    void init_Entity_withHalfGrowingTimer(gameentity::Entity entity) {
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& growing_timer = earr::enum_array_at(timers->increment, 
            +gamecomp::CreatureProgressTimerIncrement::Growing);

        progresstimer_util.start(growing_timer.base);

        growing_timer.base.value = 50.0f;
        growing_timer.base.isfull = false;
    }


    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};




SCENARIO("Start growing-timer if its not started") {
    GIVEN("Entity with not started growing-timer") {
        CreatureTestData creatureTestData;
        CreatureGrowingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        // auto battlerstatuses =
        // entity.component<gamecomp::BattlerStatusesComponent>();
        // auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();


        app.init_Entity_NotStartedGrowingTimer(entity);

        gamecomp::ProgressTimerIncrement& growing_timer = earr::enum_array_at(timers->increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("growing-timer is started") {
                CHECK(growing_timer.base.timer.isstart);
            }
        }
    }
}


SCENARIO("Pause growing-Timer by full Growing") {
    GIVEN("Entity with full growing timer") {
        CreatureTestData creatureTestData;
        CreatureGrowingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        // auto battlerstatuses =
        // entity.component<gamecomp::BattlerStatusesComponent>();
        // auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();


        app.init_Entity_withFullGrowingTimer(entity);

        gamecomp::ProgressTimerIncrement& growing_timer = earr::enum_array_at(timers->increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);
            
        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("growing-timer is paused") {
                CHECK(growing_timer.base.timer.ispause);
            }
        }
    }
}



SCENARIO("Emit Increment-Growing-Event then the body size is reached") {
    GIVEN("Entity with full growing-timer") {
        CreatureTestData creatureTestData;
        CreatureGrowingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        // auto battlerstatuses =
        // entity.component<gamecomp::BattlerStatusesComponent>();
        // auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();


        app.init_Entity_withFullGrowingTimer(entity);

        gamecomp::ProgressTimerIncrement& growing_timer = earr::enum_array_at(timers->increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);


        WHEN("emit Growing-Event with addvalue 1.0") {
            app.emit_event<gameevent::ProgressTimerIncrementEvent>(
                entity, gamecomp::CreatureProgressTimerIncrement::Growing,
                creatureTestData.CREATURELEVEL, 1.0f);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("growing-timer is paused") {
                    CHECK(growing_timer.base.timer.ispause);
                }
                THEN("body size is reached") {
                    CHECK(body->bodysize >
                          creatureTestData.MIN_BODYSIZE);
                }
            }
        }
    }
}



SCENARIO("Emit Increment-Growing-Event with burst of growth then the body size "
         "is reached to maximum") {
    GIVEN("Entity with full growing timer") {
        CreatureTestData creatureTestData;
        CreatureGrowingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        // auto battlerstatuses =
        // entity.component<gamecomp::BattlerStatusesComponent>();
        // auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();


        app.init_Entity_withFullGrowingTimer(entity);

        gamecomp::ProgressTimerIncrement& growing_timer = earr::enum_array_at(timers->increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);


        WHEN("emit Growing-Event with addvalue 100.0") {
            app.emit_event<gameevent::ProgressTimerIncrementEvent>(
                entity, gamecomp::CreatureProgressTimerIncrement::Growing,
                creatureTestData.CREATURELEVEL, 100.0f);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("growing-timer is paused") {
                    CHECK(growing_timer.base.timer.ispause);
                }
                THEN("body size is reached") {
                    CHECK(body->bodysize >
                          creatureTestData.MIN_BODYSIZE);
                }
                THEN("body has maximum bodysize") {
                    CHECK(creatureTestData.MAX_BODYSIZE_GENE ==
                          doctest::Approx(body->bodysize).epsilon(0.01));
                }
            }
        }
    }
}