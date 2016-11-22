#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureBattlerSystem.h"


class CreatureBattlerSystemApplication : public gamesystem::Application {
    private:
    data::CreatureBattlerStatus blind_status_;
    data::CreatureBattlerStatus confuse_status_;

    void init_BattlerStatus_Blind_HalfHitRateFactor() {

        this->blind_status_.setName("Blind");
        this->blind_status_.setHitRate(0.5f);

        this->datamanager.saveCreatureBattlerStatus(this->blind_status_);
    }

    void init_BattlerStatus_Confuse_AtkAll() {

        this->confuse_status_.setName("Confuse");
        this->confuse_status_.setRestriction(
            data::StatusRestrictionOption::AtkAll);

        this->datamanager.saveCreatureBattlerStatus(this->confuse_status_);
    }

    public:
    gameentity::DataManager datamanager;
    std::shared_ptr<gamesystem::CreatureBattlerSystem> creatureBattlerSystem;

    CreatureBattlerSystemApplication() {
        init_BattlerStatus_Blind_HalfHitRateFactor();
        init_BattlerStatus_Confuse_AtkAll();

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
            this->blind_status_.getName());
    }


    void init_Entity_withBattlerStatusRestrictionOptionAtkAll(
        gameentity::Entity entity) {
        auto creature_battlerstatuses =
            entity.component<gamecomp::BattlerStatusesComponent>();

        creature_battlerstatuses->statuses_name.push_back(
            this->confuse_status_.getName());
    }


    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity update HitRate") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update entities") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("hitrate is set") {
                CHECK(creature_battler->hitrate == creatureTestData.HITRATE);
            }
        }
    }
}

SCENARIO("Creature Entity with BattlerStatus and update HitRate to Half") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_withBattlerStatusHalfHitRateFactor(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update entities") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("hitrate is set") {
                CHECK(creature_battler->hitrate ==
                      creatureTestData.HITRATE_HALF);
            }
        }
    }
}



SCENARIO("Creature Entity update Critical HitRate") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update entities") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("critical hitrate is set") {
                CHECK(creature_battler->critical_hitrate ==
                      creatureTestData.CRITICAL_HITRATE);
            }
        }
    }
}



SCENARIO("Creature Entity update EvaRate") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update entities") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("evarate is set") {
                CHECK(creature_battler->evarate == creatureTestData.EVARATE);
            }
        }
    }
}



SCENARIO("Creature Entity with BattlerStatus then update "
         "StatusRestrictionOption to AtkAll") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        
        CreatureBattlerSystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_withBattlerStatusRestrictionOptionAtkAll(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimers>();
        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        WHEN("update entities") {
            app.update(CreatureBattlerSystemApplication::FAKE_TIMEDELTA);

            THEN("StatusRestrictionOption is AtkAll") {
                CHECK(creature_battler->status_restriction ==
                      +data::StatusRestrictionOption::AtkAll);
            }
        }
    }
}