#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureDeadSystem.h"

class CreatureMakeDeadEventListenerMockup
    : public gamesystem::Listener<gameevent::CreatureMakeDeadEvent> {
    public:
    bool emitevent = false;

    CreatureMakeDeadEventListenerMockup() = default;

    void update(const gameevent::CreatureMakeDeadEvent& /*event*/,
                EntityManager& /*entities*/, EventBus& /*events*/,
                TimeDelta /*dt*/) override {
        this->emitevent = true;
    }
};

class CreatureDeadSystemApplication
    : public gamesystem::Application {
    public:
    std::shared_ptr<CreatureMakeDeadEventListenerMockup> eventlistenermockup =
        std::make_shared<CreatureMakeDeadEventListenerMockup>();

    std::shared_ptr<gamesystem::CreatureDeadSystem>
        creatureDeadSystem =
            std::make_shared<gamesystem::CreatureDeadSystem>();

    CreatureDeadSystemApplication() {
        this->addListener<gameevent::CreatureMakeDeadEvent>(
            this->eventlistenermockup);
        this->addListener<gameevent::CreatureMakeDeadEvent>(
            this->creatureDeadSystem);
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};




SCENARIO("Creature Entity emit dead-Event to make creature dead and pause lifetimer") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureDeadSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        auto life =
            entity.component<gamecomp::CreatureLifeComponent>();

        auto timers =
            entity.component<gamecomp::CreatureProgressTimersComponent>();

        WHEN("emit dead-Event") {
            app.emit_event<gameevent::CreatureMakeDeadEvent>(entity, gamecomp::CauseOfDeath::Unknown);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                REQUIRE(app.eventlistenermockup->emitevent);

                THEN("has zero hp") { CHECK(util::iszero(creature_battler->hp)); }

                THEN("has zero mp") { CHECK(util::iszero(creature_battler->mp)); }

                THEN("is dead") { CHECK(life->isdead); }

            }
        }
    }
}


SCENARIO("Creature Entity emit dead-Event to pause lifetimer") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureDeadSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        auto life =
            entity.component<gamecomp::CreatureLifeComponent>();

        auto timers =
            entity.component<gamecomp::CreatureProgressTimersComponent>();

        WHEN("emit dead-Event") {
            app.emit_event<gameevent::CreatureMakeDeadEvent>(entity, gamecomp::CauseOfDeath::Unknown);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                REQUIRE(app.eventlistenermockup->emitevent);

                THEN("lifetimer is paused") { CHECK(timers->lifetimer.ispause); }
            }
        }
    }
}

