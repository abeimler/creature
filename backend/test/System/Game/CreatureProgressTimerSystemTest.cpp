#include <chrono>
#include <thread>

#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureProgressTimerSystem.h"


class ProgressTimerCallbackEventListenerMockup
    : public gamesystem::Listener<gameevent::ProgressTimerCallbackEvent> {
    public:
    bool emitevent = false;
    size_t callcount = 0;

    ProgressTimerCallbackEventListenerMockup() = default;

    void update(const gameevent::ProgressTimerCallbackEvent&  /*event*/,
                EntityManager&  /*entities*/, EventBus&  /*events*/,
                TimeDelta  /*dt*/) override {
        this->emitevent = true;
        this->callcount++;
    }
};

class ProgressTimerIncrementEventListenerMockup
    : public gamesystem::Listener<gameevent::ProgressTimerIncrementEvent> {
    public:
    bool emitevent = false;
    size_t callcount = 0;
    double addvalue = 0;

    ProgressTimerIncrementEventListenerMockup() = default;

    void update(const gameevent::ProgressTimerIncrementEvent& event,
                EntityManager&  /*entities*/, EventBus&  /*events*/,
                TimeDelta  /*dt*/) override {
        this->emitevent = true;
        this->callcount++;
        this->addvalue += event.addvalue;
    }
};


class CreatureProgressTimerSystemApplication : public gamesystem::Application {
    private:

    public:
    std::shared_ptr<ProgressTimerCallbackEventListenerMockup> callback_eventlistenermockup =
        std::make_shared<ProgressTimerCallbackEventListenerMockup>();
    std::shared_ptr<ProgressTimerIncrementEventListenerMockup> increment_eventlistenermockup =
        std::make_shared<ProgressTimerIncrementEventListenerMockup>();

    std::shared_ptr<gamesystem::CreatureProgressTimerSystem> creatureProgressTimerSystem =
            std::make_shared<gamesystem::CreatureProgressTimerSystem>();

    CreatureProgressTimerSystemApplication() {
        this->addSystem(this->creatureProgressTimerSystem);
        this->addListener<gameevent::ProgressTimerCallbackEvent>(this->callback_eventlistenermockup);
        this->addListener<gameevent::ProgressTimerIncrementEvent>(this->increment_eventlistenermockup);
    }


    gameentity::Entity create_Entity_ProgressTimers(gameentity::EntityManager& entities,
                                                 std::chrono::milliseconds waittime) {

        gameentity::CreatureEntityCreator creaturecreator;

        gameentity::Entity entity = entities.create();

        gamecomp::CreatureProgressTimersComponent timers =
            creaturecreator.createCreatureProgressTimers();
        timers.creaturelevel = creaturelevel;
        
        earr::enum_array_at(earr::enum_array_at(timers.timer, timertype).waittime,
                    creaturelevel) = waittime;
        earr::enum_array_at(
            earr::enum_array_at(timers.callback, timertype_callback).base.waittime,
            creaturelevel) = waittime;
        earr::enum_array_at(
            earr::enum_array_at(timers.increment, timertype_increment).base.waittime,
            creaturelevel) = waittime;
        earr::enum_array_at(
            earr::enum_array_at(timers.starvation, starvationphase).base.waittime,
            creaturelevel) = waittime;
        earr::enum_array_at(
            earr::enum_array_at(timers.memory, activity).shortterm.base.waittime,
            creaturelevel) = waittime;
        earr::enum_array_at(
            earr::enum_array_at(timers.memory, activity).mediumterm.base.waittime,
            creaturelevel) = waittime;

        entity.assign<gamecomp::CreatureProgressTimersComponent>(timers);

        return entity;
    }


    gameentity::Entity
    create_Entity_ProgressTimersAllWaitTime(gameentity::EntityManager& entities,
                                            std::chrono::milliseconds waittime) {
        gameentity::CreatureEntityCreator creaturecreator;

        gameentity::Entity entity = entities.create();

        gamecomp::CreatureProgressTimersComponent timers =
            creaturecreator.createCreatureProgressTimers();
        timers.creaturelevel = creaturelevel;

        for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            earr::enum_array_at(earr::enum_array_at(timers.timer, timertype).waittime,
                        creaturelevel) = waittime;
        }
        for (auto timertype_callback :
            earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.callback, timertype_callback).base.waittime,
                creaturelevel) = waittime;
        }
        for (auto timertype_increment :
            earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            earr::enum_array_at(
                earr::enum_array_at(timers.increment, timertype_increment).base.waittime,
                creaturelevel) = waittime;
        }

        entity.assign<gamecomp::CreatureProgressTimersComponent>(timers);

        return entity;
    }

    void init_StartAllProgTimers(gamecomp::CreatureProgressTimersComponent& timers) {
        gamecomputil::ProgressTimerUtil progtimer_util;
        data::CreatureLevel creaturelevel = timers.creaturelevel;

        for (auto timertype : earr::Enum<gamecomp::CreatureProgressTimer>()) {
            progtimer_util.start(earr::enum_array_at(timers.timer, timertype));
        }
        for (auto timertype_callback :
            earr::Enum<gamecomp::CreatureProgressTimerCallback>()) {
            progtimer_util.start(
                earr::enum_array_at(timers.callback, timertype_callback).base);
        }
        for (auto timertype_increment :
            earr::Enum<gamecomp::CreatureProgressTimerIncrement>()) {
            progtimer_util.start(
                earr::enum_array_at(timers.increment, timertype_increment).base);
        }
    }

    static constexpr gamecomp::CreatureProgressTimer timertype = gamecomp::CreatureProgressTimer::Hungry;
    static constexpr gamecomp::CreatureProgressTimerCallback timertype_callback = gamecomp::CreatureProgressTimerCallback::Digestion;
    static constexpr gamecomp::CreatureProgressTimerIncrement timertype_increment = gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry;
    static constexpr data::CreatureLevel creaturelevel = data::CreatureLevel::Child;
    static constexpr gamecomp::StarvationPhase starvationphase = gamecomp::StarvationPhase::None;
    static constexpr gamecomp::CreatureActivity activity = gamecomp::CreatureActivity::Noting;

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};

constexpr gamecomp::CreatureProgressTimer CreatureProgressTimerSystemApplication::timertype;
constexpr gamecomp::CreatureProgressTimerCallback CreatureProgressTimerSystemApplication::timertype_callback;
constexpr gamecomp::CreatureProgressTimerIncrement CreatureProgressTimerSystemApplication::timertype_increment;
constexpr data::CreatureLevel CreatureProgressTimerSystemApplication::creaturelevel;
constexpr gamecomp::StarvationPhase CreatureProgressTimerSystemApplication::starvationphase;
constexpr gamecomp::CreatureActivity CreatureProgressTimerSystemApplication::activity;




SCENARIO("Wait 100% of waitTime to fill Value to 100%") {
    GIVEN("ProgressTimer with 100 ms waittime") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);

        WHEN("start timer and sleep waittime") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(waittime);

            AND_WHEN("update entities") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("ProgressTimer value is 100%") {
                    CHECK(progtimer.value >= 100.0f);
                }
                AND_THEN("overlayvalue may not 0%") {
                    CHECK(progtimer.overlayvalue >= 0.0f);
                    CHECK(progtimer.overlayvalue < 100.0f);
                }
            }
        }
    }
}


SCENARIO("Wait 200% of waitTime to fill Value to 100% with overlay") {
    GIVEN("ProgressTimer with 100 ms waittime") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);

        WHEN("start timer and sleep 2 x waittime") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(2 * waittime);

            AND_WHEN("update entities") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("is value 100%") { 
                    CHECK(progtimer.value >= 100.0f); 
                }
                AND_THEN("overlayvalue is not 0%") {
                    CHECK(progtimer.overlayvalue >= 0.0f);
                }
            }
        }
    }
}



SCENARIO("Wait 50% of waitTime to fill Value to 50%") {
    GIVEN("ProgressTimer with 100 ms waittime") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);


        WHEN("start timer and sleep waittime/2") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(waittime / 2);

            AND_WHEN("update manager") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("value is 50% but over 100%)") {
                    CHECK(progtimer.value >= 50.0f);
                    CHECK(progtimer.value < 100.0f);
                }
                AND_THEN("overlay is 0%") {
                    CHECK(util::iszero(progtimer.overlayvalue));
                }
            }
        }
    }
}



SCENARIO("Wait 50% of waitTime with ValueFactor 2 to fill Value to 100%") {
    GIVEN("ProgressTimer with 100 ms waittime and factor 2") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);

        progtimer.factor = 2.0f;

        WHEN("start timer and sleep waittime/2") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(waittime / 2);

            AND_WHEN("update manager") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("value is 100%") { 
                    CHECK(progtimer.value >= 100.0f); 
                }
                AND_THEN("overlayvalue may not 0%") {
                    CHECK(progtimer.overlayvalue >= 0.0f);
                    CHECK(progtimer.overlayvalue < 100.0f);
                }
            }
        }
    }
}



SCENARIO("Wait 50% of waitTime with ValueFactor 4 to fill Value to 100% with overlay") {
    GIVEN("ProgressTimer with 100 ms waittime and factor 4") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);

        progtimer.factor = 4.0f;

        WHEN("start timer and sleep waittime/2") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(waittime / 2);

            AND_WHEN("update manager") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("value is 100%") { 
                    CHECK(progtimer.value >= 100.0f); 
                }
                THEN("with overlayvalue") {
                    CHECK(progtimer.overlayvalue >= 0.0f);
                }
            }
        }
    }
}


SCENARIO("Wait 100% of waitTime with ValueFactor 0.5 to fill Value to 50%") {
    GIVEN("ProgressTimer with 100 ms waittime and factor 0.5") {
        //computil::DateTimerUtil datetimer_util;
        gamecomputil::ProgressTimerUtil progresstimer_util;
        std::chrono::milliseconds waittime = std::chrono::milliseconds(100);

        CreatureProgressTimerSystemApplication app;
        auto& entities = app.getEntityManager();

        auto entity = app.create_Entity_ProgressTimers(entities, waittime);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& progtimer =
            earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);

        progtimer.factor = 0.5f;

        WHEN("start timer and sleep waittime") {
            progresstimer_util.start(progtimer);
            std::this_thread::sleep_for(waittime);

            AND_WHEN("update manager") {
                app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

                THEN("value is 50% but not over 100%") {
                    CHECK(progtimer.value >= 50.0f);
                    CHECK(progtimer.value < 100.0f);
                }
                THEN("overlay is 0%") {
                    CHECK(util::iszero(progtimer.overlayvalue));
                }
            }
        }
    }
}



TEST_CASE("Wait 100% of waitTime with pause to fill Value to 100%") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimer& progtimer =
        earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);


    progresstimer_util.start(progtimer);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    progresstimer_util.pause(progtimer);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("value is 100%") { 
        CHECK(progtimer.value >= 100.0f); 
    }

    SUBCASE("overlayvalue may not 0%") {
        CHECK(progtimer.overlayvalue >= 0.0f);
        CHECK(progtimer.overlayvalue < 100.0f);
    }
}




TEST_CASE("Wait 2*50% of waitTime with pause unpause to fill Value to 100%") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(50);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimer& progtimer =
        earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);


    progresstimer_util.start(progtimer);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    progresstimer_util.pause(progtimer);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    progresstimer_util.unpause(progtimer);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("value is 100%") { 
        CHECK(progtimer.value >= 100.0f); 
    }

    SUBCASE("overlayvalue may not 0%") {
        CHECK(progtimer.overlayvalue >= 0.0f);
        CHECK(progtimer.overlayvalue < 100.0f);
    }
}




TEST_CASE("Wait 2*100% of waitTime with restart to fill Value to 100%") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimer& progtimer =
        earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);




    progresstimer_util.start(progtimer);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    progresstimer_util.restart(progtimer);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);


    SUBCASE("value is 100%") { 
        CHECK(progtimer.value >= 100.0f); 
    }

    SUBCASE("overlayvalue may not 0%") {
        CHECK(progtimer.overlayvalue >= 0.0f);
        CHECK(progtimer.overlayvalue < 100.0f);
    }
}



TEST_CASE("Wait 2*100% of waitTime with stop to reset Value to 0%") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimer& progtimer =
        earr::enum_array_at(timers->timer, CreatureProgressTimerSystemApplication::timertype);


    progresstimer_util.start(progtimer);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    progresstimer_util.stop(progtimer);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("value is 0%") { 
        CHECK(util::iszero(progtimer.value)); 
    }

    SUBCASE("overlay is 0%") { 
        CHECK(util::iszero(progtimer.overlayvalue)); 
    }
}



TEST_CASE("Wait 100% of waitTime to trigger Callback") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimerCallback& progtimer =
        earr::enum_array_at(timers->callback, CreatureProgressTimerSystemApplication::timertype_callback);


    auto listener = app.callback_eventlistenermockup;

    progresstimer_util.start(progtimer.base);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("is value 100%") { 
        CHECK(progtimer.base.value >= 100.0f); 
    }

    SUBCASE("overlayvalue may not 0%") {
        CHECK(progtimer.base.overlayvalue >= 0.0f);
        CHECK(progtimer.base.overlayvalue < 100.0f);
    }

    SUBCASE("is trigger callback flag set") { 
        CHECK(listener->emitevent); 
    }

    SUBCASE("call callback once") {
        CHECK(listener->callcount == 1u);
    }
}


TEST_CASE("Wait 50% of waitTime and trigger increment") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(50);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimerIncrement& progtimer =
        earr::enum_array_at(timers->increment, CreatureProgressTimerSystemApplication::timertype_increment);


    auto listener = app.increment_eventlistenermockup;


    progresstimer_util.start(progtimer.base);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);


    SUBCASE("is value 50%") { 
        CHECK(progtimer.base.value >= 50.0f); 
    }

    SUBCASE("overlayvalue is 0%") {
        CHECK(util::iszero(progtimer.base.overlayvalue));
    }

    SUBCASE("added value is 50%") { 
        CHECK(listener->addvalue >= 50.0f); 
    }

    SUBCASE("call increment callback once") {
        CHECK(listener->callcount == 1u);
    }
}


TEST_CASE("Wait 100% of waitTime and trigger increment") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimerIncrement& progtimer =
        earr::enum_array_at(timers->increment, CreatureProgressTimerSystemApplication::timertype_increment);


    auto listener = app.increment_eventlistenermockup;

    progresstimer_util.start(progtimer.base);
    std::this_thread::sleep_for(sleeptime);


    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("is value 100%") { 
        CHECK(progtimer.base.value >= 100.0f); 
    }

    SUBCASE("overlayvalue may not 0%") {
        CHECK(progtimer.base.overlayvalue >= 0.0f);
        CHECK(progtimer.base.overlayvalue < 100.0f);
    }

    SUBCASE("added value is 100%") { 
        CHECK(listener->addvalue >= 100.0f); 
    }

    SUBCASE("call increment callback once") {
        CHECK(listener->callcount == 1u);
    }
}



TEST_CASE("Wait 50% of waitTime with factor 2 and trigger increment") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(50);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimerIncrement& progtimer =
        earr::enum_array_at(timers->increment, CreatureProgressTimerSystemApplication::timertype_increment);


    auto listener = app.increment_eventlistenermockup;


    progtimer.addvalue_per_percent = 2.0f;

    progresstimer_util.start(progtimer.base);
    std::this_thread::sleep_for(sleeptime);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);

    SUBCASE("value is 50%") { 
        CHECK(progtimer.base.value >= 50.0f); 
    }

    SUBCASE("overlayvalue is 0%") {
        CHECK(util::iszero(progtimer.base.overlayvalue));
    }

    SUBCASE("added value is 100%") { 
        CHECK(listener->addvalue >= 100.0f); 
    }

    SUBCASE("call increment callback once") {
        CHECK(listener->callcount == 1u);
    }
}



TEST_CASE("Wait 3*100% of waitTime to trigger Increment more times (endless)") {
    std::chrono::milliseconds waittime = std::chrono::milliseconds(100);
    std::chrono::milliseconds sleeptime = std::chrono::milliseconds(100);

    //computil::DateTimerUtil datetimer_util;
    gamecomputil::ProgressTimerUtil progresstimer_util;

    CreatureProgressTimerSystemApplication app;
    auto& entities = app.getEntityManager();

    auto entity = app.create_Entity_ProgressTimers(entities, waittime);

    auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
    gamecomp::ProgressTimerIncrement& progtimer =
        earr::enum_array_at(timers->increment, CreatureProgressTimerSystemApplication::timertype_increment);


    auto listener = app.increment_eventlistenermockup;


    progtimer.isendless = true;
    progresstimer_util.start(progtimer.base);

    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);
    std::this_thread::sleep_for(sleeptime);
    app.update(CreatureProgressTimerSystemApplication::FAKE_TIMEDELTA);


    SUBCASE("is added value >= 100%") { 
        CHECK(listener->addvalue >= 100.0f); 
    }

    float endvalue = 300.0f;
    SUBCASE("added value is 300%") { 
        CHECK(listener->addvalue >= endvalue); 
    }

    SUBCASE("call increment callback 3 times") {
        CHECK(listener->callcount == 3);
    }
}
