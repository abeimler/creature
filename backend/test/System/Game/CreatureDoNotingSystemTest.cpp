#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureDoNotingSystem.h"

class CreatureDoNotingEventListenerMockup
    : public gamesystem::Listener<gameevent::CreatureDoNotingEvent> {
    public:
    bool emitevent = false;

    CreatureDoNotingEventListenerMockup() = default;

    void update(const gameevent::CreatureDoNotingEvent& /*event*/,
                EntityManager& /*entities*/, EventBus& /*events*/,
                TimeDelta /*dt*/) override {
        this->emitevent = true;
    }
};

class CreatureDoNotingSystemApplication : public gamesystem::Application {
    public:
    const char* HUNGRY_STATUS_NAME = "Hungry";

    std::shared_ptr<CreatureDoNotingEventListenerMockup> eventlistenermockup =
        std::make_shared<CreatureDoNotingEventListenerMockup>();

    std::shared_ptr<gamesystem::CreatureDoNotingSystem> creatureDoNotingSystem =
        std::make_shared<gamesystem::CreatureDoNotingSystem>();

    CreatureDoNotingSystemApplication() {
        this->addSystem(this->creatureDoNotingSystem);
        this->addListener(this->eventlistenermockup);
    }

    void init_Entity_withHungryStatus(gameentity::EntityManager& entities, gameentity::Entity entity) {
        // gamecomputil::ProgressTimerUtil progresstimer_util;

        auto& timers =
            entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        gamecomp::ProgressTimer& hungry_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::Hungry);

        hungry_timer.value = 100.0f;
        hungry_timer.isfull = true;

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hungry) =
            true;

        auto& battlerstatuses =
            entities.get<gamecomp::BattlerStatusesComponent>(entity);
        battlerstatuses.statuses_name.push_back(HUNGRY_STATUS_NAME);
    }

    void init_Entity_isBusy(gameentity::EntityManager& entities, gameentity::Entity entity) {
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        life.isbusy = true;
    }

    void init_Entity_isNotBusy(gameentity::EntityManager& entities, gameentity::Entity entity) {
        auto life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        life.isbusy = false;
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity update doNoting then emit doNoting-Event") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("doNoting-Event is emmited") {
                CHECK(app.eventlistenermockup->emitevent);
            }
        }
    }
}

SCENARIO("Creature Entity update doNoting then creatire is not busy") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("is not busy") { CHECK_FALSE(life.isbusy); }
        }
    }
}


SCENARIO("Creature Entity without statuses then set isbusy to false") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_isBusy(entities, entity);

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("busy is set") { CHECK_FALSE(life.isbusy); }
        }
    }
}

SCENARIO("Creature Entity with Hungry status is not busy") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_isBusy(entities, entity);
        app.init_Entity_withHungryStatus(entities, entity);


        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        AND_WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("busy is not set") { CHECK_FALSE(life.isbusy); }
        }
    }
}