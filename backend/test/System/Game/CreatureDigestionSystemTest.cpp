#include <thread>

#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureDigestionSystem.h"
#include "System/Game/CreatureDigestionCallbackListener.h"
#include "System/Game/CreatureProgressTimerSystem.h"


class CreatureDigestionSystemApplication : public gamesystem::Application {
    private:

    public:

    std::shared_ptr<gamesystem::CreatureProgressTimerSystem> creatureProgressTimerSystem;
    std::shared_ptr<gamesystem::CreatureDigestionCallbackListener> creatureDigestionCallbackListener;
    std::shared_ptr<gamesystem::CreatureDigestionSystem> creatureDigestionSystem;

    CreatureDigestionSystemApplication() {
        this->creatureProgressTimerSystem =
                std::make_shared<gamesystem::CreatureProgressTimerSystem>();
        this->creatureDigestionCallbackListener =
            std::make_shared<gamesystem::CreatureDigestionCallbackListener>();
        this->creatureDigestionSystem =
            std::make_shared<gamesystem::CreatureDigestionSystem>();

        this->addSystem(this->creatureProgressTimerSystem);
        this->addListener(this->creatureDigestionCallbackListener);
        this->addSystem(this->creatureDigestionSystem);
    }



    void init_Entity_withEmptyDigestionTimer(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();

        auto& digestion_timer = earr::enum_array_at(timers->callback, 
            +gamecomp::CreatureProgressTimerCallback::Digestion);
        gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(digestion_progresstimer, time, 1.0f);
        progresstimer_util.start(digestion_progresstimer);

        digestion_progresstimer.value = 0.0f;
        digestion_progresstimer.isfull = false;
    }

    void init_Entity_withFullDigestionTimer(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& digestion_timer = earr::enum_array_at(timers->callback, 
            +gamecomp::CreatureProgressTimerCallback::Digestion);
        gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(digestion_progresstimer, time, 1.0f);
        progresstimer_util.start(digestion_progresstimer);

        digestion_progresstimer.value = 100.0f;
        digestion_progresstimer.isfull = true;
        digestion_progresstimer.overlayvalue = 0.0f;
    }

    void
    init_Entity_withFullDigestionTimerWithOverlay(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& digestion_timer = earr::enum_array_at(timers->callback, 
            +gamecomp::CreatureProgressTimerCallback::Digestion);
        gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(digestion_progresstimer, time, 1.0f);
        progresstimer_util.start(digestion_progresstimer);

        digestion_progresstimer.value = 100.0f;
        digestion_progresstimer.isfull = true;
        digestion_progresstimer.overlayvalue = 200.0f;
    }


    void init_Entity_withFullHungerTimer(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& hungry_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Hungry);
        gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(hungry_progresstimer, time, 1.0f);
        progresstimer_util.start(hungry_progresstimer);

        hungry_progresstimer.value = 100.0f;
        hungry_progresstimer.isfull = true;
        hungry_progresstimer.overlayvalue = 0.0f;
    }

    void
    init_Entity_withFullHungerTimerWithOverlay(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& hungry_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Hungry);
        gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(hungry_progresstimer, time, 1.0f);
        progresstimer_util.start(hungry_progresstimer);

        hungry_progresstimer.value = 100.0f;
        hungry_progresstimer.isfull = true;
        hungry_progresstimer.overlayvalue = gamesystem::CreatureDigestionCallbackListener::PAUSE_DIGESTION_BY_HUNGRY_OVERLAYVALUE;
    }

    void
    init_Entity_withFullPauseDigestionHungryTimer(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        init_Entity_withFullHungerTimerWithOverlay(entity);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& pause_digistation_timer = earr::enum_array_at(timers->callback,
            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry);
        gamecomp::ProgressTimer& pause_digistation_progresstimer =
            pause_digistation_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();

        progresstimer_util.init(pause_digistation_progresstimer, time, 1.0f);
        progresstimer_util.start(pause_digistation_progresstimer);

        pause_digistation_progresstimer.value = 100.0f;
        pause_digistation_progresstimer.isfull = true;
    }

    void
    init_Entity_withFullPoopStack(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        //gamecomputil::ProgressTimerUtil progresstimer_util;

        auto hunger = entity.component<gamecomp::CreatureHungerComponent>();
        auto gene = entity.component<gamecomp::CreatureGeneComponent>();

        hunger->poopstack = gene->max_poopstack;
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Entity with full digestion-timer poop once") {
    GIVEN("Entity with full digestion-timer") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto oldbody = entity.component<gamecomp::CreatureBodyComponent>();
        auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimer(entity);

        auto oldweight = oldbody->weight;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            auto newbody = entity.component<gamecomp::CreatureBodyComponent>();
            auto newweight = newbody->weight;

            THEN("one poop") { 
                CHECK(1 == hunger->poopstack); 
            }

            THEN("lost weight") { 
                CHECK(newweight < oldweight); 
            }
        }
    }
}


SCENARIO("Entity with empty digestion-timer and none poop") {
    GIVEN("Entity with empty digestion-timer") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withEmptyDigestionTimer(entity);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("none poop") { 
                CHECK(0 == hunger->poopstack); 
            }
        }
    }
}

SCENARIO("Entity with full digestion-timer with overlay to poop more then one times") {
    GIVEN("Entity with full digestion-timer and overlay") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        //auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimerWithOverlay(entity);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("more then one poop") {
                CHECK(hunger->poopstack > 1);
            }
        }
    }
}




SCENARIO("Entity with full digestion and hunger overlay then "
         "pause digestion timer is started") {
    GIVEN("Creature Entity with full digestion and hunger overlay") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimer(entity);
        app.init_Entity_withFullHungerTimerWithOverlay(entity);


        auto& pause_digistation_timer = earr::enum_array_at(timers->callback,
            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry);
        gamecomp::ProgressTimer& pause_digistation_progresstimer =
            pause_digistation_timer.base;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("pause digestion timer is started") {
                CHECK(pause_digistation_progresstimer.timer.isstart);
            }
        }
    }
}


SCENARIO("Entity with full digestion pause hunger timer then "
         "pause digestion") {
    GIVEN("Creature Entity with full digestion pause timer") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimer(entity);
        app.init_Entity_withFullHungerTimerWithOverlay(entity);
        app.init_Entity_withFullPauseDigestionHungryTimer(entity);


        auto& digestion_timer = earr::enum_array_at(timers->callback, 
            +gamecomp::CreatureProgressTimerCallback::Digestion);
        gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("digestion is paused") {
                CHECK(digestion_progresstimer.timer.ispause);
            }
        }
    }
}



SCENARIO("Entity with full digestion max poop stack then "
         "start full poop stack timer") {
    GIVEN("Creature Entity with full digestion max poop stack") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimer(entity);
        app.init_Entity_withFullPoopStack(entity);


        auto& full_poop_stack_timer = earr::enum_array_at(timers->callback,
            +gamecomp::CreatureProgressTimerCallback::FullPoopStack);
        gamecomp::ProgressTimer& full_poop_stack_progresstimer =
            full_poop_stack_timer.base;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("full poop stack timer is started") {
                CHECK(full_poop_stack_progresstimer.timer.isstart);
            }
        }
    }
}



SCENARIO("Entity with pause digestion when no hunger then "
         "unpause digestion") {
    GIVEN("Creature Entity with full digestion pause timer") {
        CreatureTestData creatureTestData;
        CreatureDigestionSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto body = entity.component<gamecomp::CreatureBodyComponent>();
        //auto hunger = entity.component<gamecomp::CreatureHungerComponent>();

        app.init_Entity_withFullDigestionTimer(entity);
        app.init_Entity_withFullHungerTimerWithOverlay(entity);
        app.init_Entity_withFullPauseDigestionHungryTimer(entity);

        auto& hungry_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Hungry);
        gamecomp::ProgressTimer& hungry_progresstimer = hungry_timer;

        auto& digestion_timer = earr::enum_array_at(timers->callback, 
            +gamecomp::CreatureProgressTimerCallback::Digestion);
        gamecomp::ProgressTimer& digestion_progresstimer = digestion_timer.base;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            REQUIRE(digestion_progresstimer.timer.ispause);

            AND_WHEN("none hunger") {
                hungry_progresstimer.value = 0.0;
                hungry_progresstimer.isfull = false;
                hungry_progresstimer.overlayvalue = 0.0;


                AND_WHEN("update manager") {
                    app.update(app.FAKE_TIMEDELTA);
                    
                    THEN("digestion is unpaused") {
                        CHECK_FALSE(digestion_progresstimer.timer.ispause);
                    }
                }
            }
        }
    }
}

