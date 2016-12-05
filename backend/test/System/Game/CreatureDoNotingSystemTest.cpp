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

class CreatureDoNotingSystemApplication
    : public gamesystem::Application {
    public:
    const char* HUNGRY_STATUS_NAME = "Hungry";

    std::shared_ptr<CreatureDoNotingEventListenerMockup> eventlistenermockup =
        std::make_shared<CreatureDoNotingEventListenerMockup>();

    std::shared_ptr<gamesystem::CreatureDoNotingSystem>
        creatureDoNotingSystem =
            std::make_shared<gamesystem::CreatureDoNotingSystem>();

    CreatureDoNotingSystemApplication() {
        this->addSystem(this->creatureDoNotingSystem);
        this->addListener(this->eventlistenermockup);
    }

    void init_Entity_withHungryStatus(gameentity::Entity entity) {
        //gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& hungry_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Hungry);

        hungry_timer.value = 100.0f;
        hungry_timer.isfull = true;

        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Hungry) = true;

        auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        battlerstatuses->statuses_name.push_back(HUNGRY_STATUS_NAME);
    }

    void init_Entity_isBusy(gameentity::Entity entity) {
        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        life->isbusy = true;
    }

    void init_Entity_isNotBusy(gameentity::Entity entity) {
        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        life->isbusy = false;
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

        auto life =
            entity.component<gamecomp::CreatureLifeComponent>();

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("is not busy") { 
                CHECK_FALSE(life->isbusy); 
            }
        }
    }
}


SCENARIO("Creature Entity without statuses then set isbusy to false") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_isBusy(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("busy is set") { 
                CHECK_FALSE(life->isbusy); 
            }
        }
    }
}

SCENARIO("Creature Entity with Hungry status is not busy") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureDoNotingSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_isBusy(entity);
        app.init_Entity_withHungryStatus(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();

        AND_WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("busy is not set") { 
                CHECK_FALSE(life->isbusy); 
            }
        }
    }
}