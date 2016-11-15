#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureBattlerSystem.h"


class CreatureBattlerSystemApplication : public gamesystem::Application {
    private:
    data::CreatureBattlerStatus halfHitRateFactor_;

    void init_BattlerStatus_HalfHitRateFactor() {

        this->halfHitRateFactor_.setName("Blind");
        this->halfHitRateFactor_.setHitRate(0.5f);

        this->datamanager.saveCreatureBattlerStatus(halfHitRateFactor_);
    }

    public:
    gameentity::DataManager datamanager;
    std::shared_ptr<gamesystem::CreatureBattlerSystem> creatureBattlerSystem;

    CreatureBattlerSystemApplication() {
        init_BattlerStatus_HalfHitRateFactor();

        this->creatureBattlerSystem =
            std::make_shared<gamesystem::CreatureBattlerSystem>(
                this->datamanager);

        this->addSystem(this->creatureBattlerSystem);
    }

    void
    init_Entity_withBattlerStatusHalfHitRateFactor(gameentity::Entity entity) {
        auto creature_battlerstatuses =
            entity.component<gamecomp::BattlerStatusesComponent>();

        creature_battlerstatuses->statuses_name.push_back(
            this->halfHitRateFactor_.getName());
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity update HitRate") {
    GIVEN("Creature Entity") {
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = CreatureTestData::make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update manager") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("hitrate is set") {
                CHECK(creature_battler->hitrate == CreatureTestData::HITRATE);
            }
        }
    }
}

SCENARIO("Creature Entity with BattlerStatus and update HitRate to Half") {
    GIVEN("Creature Entity") {
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = CreatureTestData::make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_withBattlerStatusHalfHitRateFactor(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update manager") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("hitrate is set") {
                CHECK(creature_battler->hitrate ==
                      CreatureTestData::HITRATE_HALF);
            }
        }
    }
}



SCENARIO("Creature Entity update Critical HitRate") {
    GIVEN("Creature Entity") {
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = CreatureTestData::make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update manager") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("critical hitrate is set") {
                CHECK(creature_battler->critical_hitrate ==
                      CreatureTestData::CRITICAL_HITRATE);
            }
        }
    }
}



SCENARIO("Creature Entity update EvaRate") {
    GIVEN("Creature Entity") {
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = CreatureTestData::make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update manager") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("evarate is set") {
                CHECK(creature_battler->evarate == CreatureTestData::EVARATE);
            }
        }
    }
}
