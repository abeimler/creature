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
    std::shared_ptr<CreatureDoNotingEventListenerMockup> eventlistenermockup =
        std::make_shared<CreatureDoNotingEventListenerMockup>();

    std::shared_ptr<gamesystem::CreatureDoNotingSystem>
        creatureDoNotingSystem =
            std::make_shared<gamesystem::CreatureDoNotingSystem>();

    CreatureDoNotingSystemApplication() {
        this->addSystem(this->creatureDoNotingSystem);
        this->addListener<gameevent::CreatureDoNotingEvent>(
            this->eventlistenermockup);
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
