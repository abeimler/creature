#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureAddStatusListener.h"
#include "System/Game/CreatureBattlerAddBattlerStatusListener.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusListener.h"
#include "System/Game/CreatureMakeRunAwayListener.h"
#include "System/Game/CreatureRemoveRunAwayListener.h"
#include "System/Game/CreatureRemoveStatusListener.h"
#include "System/Game/CreatureSystem.h"


class CreatureAddRemoveStatusRunAwaySystemApplication
    : public gamesystem::Application {
    private:
    std::vector<data::CreatureBattlerStatus> getCreatureStatusList() {
        std::vector<data::CreatureBattlerStatus> statuses;

        data::CreatureBattlerStatus dead("Dead", data::CreatureStatus::Dead);
        dead.setPriority(100);
        dead.setOption(data::StatusOption::Dead, true);
        statuses.push_back(dead);

        data::CreatureBattlerStatus runaway(RUNAWAY_STATUS_NAME,
                                            data::CreatureStatus::RunAway);
        runaway.setPriority(95);
        statuses.push_back(runaway);

        data::CreatureBattlerStatus sleep(SLEEP_STATUS_NAME,
                                          data::CreatureStatus::Sleep);
        sleep.setPriority(90);
        statuses.push_back(sleep);

        data::CreatureBattlerStatus inhospital(
            "InHospital", data::CreatureStatus::InHospital);
        inhospital.setPriority(85);
        statuses.push_back(inhospital);

        data::CreatureBattlerStatus restinhospital(
            "RestInHospital", data::CreatureStatus::RestInHospital);
        restinhospital.setPriority(90);
        statuses.push_back(restinhospital);

        data::CreatureBattlerStatus rest("Rest", data::CreatureStatus::Rest);
        rest.setPriority(85);
        statuses.push_back(rest);

        data::CreatureBattlerStatus hurt("Hurt", data::CreatureStatus::Hurt);
        hurt.setPriority(85);
        statuses.push_back(hurt);

        data::CreatureBattlerStatus ill(ILL_STATUS_NAME,
                                        data::CreatureStatus::Ill);
        ill.setPriority(85);
        statuses.push_back(ill);

        data::CreatureBattlerStatus training("Training",
                                             data::CreatureStatus::Training);
        training.setPriority(85);
        statuses.push_back(training);

        data::CreatureBattlerStatus unhappy("Unhappy",
                                            data::CreatureStatus::Unhappy);
        unhappy.setPriority(70);
        statuses.push_back(unhappy);

        data::CreatureBattlerStatus happy("Happy", data::CreatureStatus::Happy);
        happy.setPriority(70);
        statuses.push_back(happy);

        data::CreatureBattlerStatus hungry(HUNGRY_STATUS_NAME,
                                           data::CreatureStatus::Hungry);
        hungry.setPriority(80);
        statuses.push_back(hungry);

        data::CreatureBattlerStatus thirsty("Thirsty",
                                            data::CreatureStatus::Thirsty);
        thirsty.setPriority(80);
        statuses.push_back(thirsty);

        data::CreatureBattlerStatus replete("Replete",
                                            data::CreatureStatus::Replete);
        replete.setPriority(70);
        statuses.push_back(replete);

        data::CreatureBattlerStatus tired("Tired", data::CreatureStatus::Tired);
        tired.setPriority(80);
        statuses.push_back(tired);

        return statuses;
    }

    void init_DataManager_AllCreatureStatuses(
        gameentity::DataManager& p_datamanager) {
        auto statuses = getCreatureStatusList();
        for (const auto& status : statuses) {
            p_datamanager.saveCreatureBattlerStatus(status);
        }
    }

    public:
    const char* HUNGRY_STATUS_NAME = "Hungry";
    const char* SLEEP_STATUS_NAME = "Sleep";
    const char* ILL_STATUS_NAME = "Ill";
    const char* RUNAWAY_STATUS_NAME = "RunAway";

    gameentity::DataManager datamanager;

    std::shared_ptr<gamesystem::CreatureAddStatusListener>
        creatureAddStatusListener;
    std::shared_ptr<gamesystem::CreatureRemoveStatusListener>
        creatureRemoveStatusListener;
    std::shared_ptr<gamesystem::CreatureBattlerAddBattlerStatusListener>
        creatureBattlerAddBattlerStatusListener;
    std::shared_ptr<gamesystem::CreatureBattlerRemoveBattlerStatusListener>
        creatureBattlerRemoveBattlerStatusListener;

    std::shared_ptr<gamesystem::CreatureSystem> creatureSystem;
    std::shared_ptr<gamesystem::CreatureMakeRunAwayListener>
        creatureMakeRunAwayListener;
    std::shared_ptr<gamesystem::CreatureRemoveRunAwayListener>
        creatureRemoveRunAwayListener;

    CreatureAddRemoveStatusRunAwaySystemApplication() {
        init_DataManager_AllCreatureStatuses(datamanager);

        this->creatureAddStatusListener =
            std::make_shared<gamesystem::CreatureAddStatusListener>(
                this->datamanager);
        this->creatureRemoveStatusListener =
            std::make_shared<gamesystem::CreatureRemoveStatusListener>(
                this->datamanager);
        this->creatureBattlerAddBattlerStatusListener = std::make_shared<
            gamesystem::CreatureBattlerAddBattlerStatusListener>(
            this->datamanager);
        this->creatureBattlerRemoveBattlerStatusListener = std::make_shared<
            gamesystem::CreatureBattlerRemoveBattlerStatusListener>(
            this->datamanager);

        this->creatureSystem =
            std::make_shared<gamesystem::CreatureSystem>(this->datamanager);

        this->creatureMakeRunAwayListener =
            std::make_shared<gamesystem::CreatureMakeRunAwayListener>();
        this->creatureRemoveRunAwayListener =
            std::make_shared<gamesystem::CreatureRemoveRunAwayListener>();

        this->addListener(this->creatureMakeRunAwayListener);
        this->addListener(this->creatureRemoveRunAwayListener);
        this->addListener(this->creatureAddStatusListener);
        this->addListener(this->creatureRemoveStatusListener);
        this->addListener(this->creatureBattlerAddBattlerStatusListener);
        this->addListener(this->creatureBattlerRemoveBattlerStatusListener);
        this->addSystem(this->creatureSystem);
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
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::Hungry) = true;

        auto& battlerstatuses =
            entities.get<gamecomp::BattlerStatusesComponent>(entity);
        battlerstatuses.statuses_name.push_back(HUNGRY_STATUS_NAME);
    }

    void init_Entity_isBusy(gameentity::EntityManager& entities, gameentity::Entity entity) {
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        life.isbusy = true;
    }

    void init_Entity_isNotBusy(gameentity::EntityManager& entities, gameentity::Entity entity) {
        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        life.isbusy = false;
    }

    void init_Entity_withStartedRunAwayTimer(gameentity::EntityManager& entities, gameentity::Entity entity,
                                             gamecomp::waittime_t waittime) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto& timers =
            entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
        auto& runawayunhappy_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy);
        gamecomp::ProgressTimer& runawayunhappy_progresstimer =
            runawayunhappy_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();
        progresstimer_util.init(runawayunhappy_progresstimer, time, 1.0f);
        runawayunhappy_progresstimer.waittime.fill(waittime);
        progresstimer_util.start(runawayunhappy_progresstimer);

        auto& psyche = entities.get<gamecomp::CreaturePsycheComponent>(entity);
        psyche.luck = 0;

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        life.causeofrunaway = gamecomp::CauseOfRunAway::Unhappy;
    }

    void init_Entity_withRunAwayStatus(gameentity::EntityManager& entities, gameentity::Entity entity,
                                       gamecomp::waittime_t waittime) {
        init_Entity_withStartedRunAwayTimer(entities, entity, waittime);

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);
        earr::enum_array_at(life.hasstatus, +data::CreatureStatus::RunAway) = true;

        auto& battlerstatuses =
            entities.get<gamecomp::BattlerStatusesComponent>(entity);
        battlerstatuses.statuses_name.push_back(RUNAWAY_STATUS_NAME);
    }

    void init_Entity_withCanGoSleepTired(gameentity::EntityManager& entities, gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        auto& timers =
            entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

        gamecomp::ProgressTimer& tired_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::Tired);
        gamecomp::ProgressTimer& tired_progresstimer = tired_timer;

        tired_progresstimer.value = creatureTestData.CANGOSLEEP_AT_TIRED;
    }

    void init_Entity_withOneHPMP(gameentity::EntityManager& entities, gameentity::Entity entity) {
        // gamecomputil::ProgressTimerUtil progresstimer_util;

        auto& creature_battler =
            entities.get<gamecomp::CreatureBattlerComponent>(entity);

        creature_battler.hp = 1;
        creature_battler.mp = 1;
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity emit makeRunAway-Event then "
         "status RunAway added") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusRunAwaySystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);

        auto runaway_waittime = std::chrono::milliseconds(1000);

        REQUIRE_FALSE(earr::enum_array_at(life.hasstatus,
                                          +data::CreatureStatus::RunAway));

        WHEN("emit makeRunAway Event") {
            app.emit_event<gameevent::CreatureMakeRunAwayEvent>(
                entity, gamecomp::CauseOfRunAway::Unhappy, runaway_waittime);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("runAway is added") {
                    CHECK(earr::enum_array_at(life.hasstatus,
                                              +data::CreatureStatus::RunAway));
                }
            }
        }
    }
}


SCENARIO("Creature Entity emit makeRunAway-Event then "
         "runAway-Timer started") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusRunAwaySystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto& timers =
            entities.get<gamecomp::CreatureProgressTimersComponent>(entity);


        auto runaway_waittime = std::chrono::milliseconds(1000);

        auto& runaway_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::RunAway);
        gamecomp::ProgressTimer& runaway_progresstimer = runaway_timer;

        WHEN("emit makeRunAway Event") {
            app.emit_event<gameevent::CreatureMakeRunAwayEvent>(
                entity, gamecomp::CauseOfRunAway::Unhappy, runaway_waittime);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("runAway-Timer is started") {
                    CHECK(runaway_progresstimer.timer.isstart);
                }

                THEN("runAway-Timer waittime is set") {
                    CHECK(earr::enum_array_at(runaway_progresstimer.waittime,
                                              creatureTestData.CREATURELEVEL) ==
                          runaway_waittime);
                }
            }
        }
    }
}


SCENARIO("Creature Entity with RunAway Status then "
         "status RunAway is removed") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusRunAwaySystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto& life = entities.get<gamecomp::CreatureLifeComponent>(entity);


        auto runaway_waittime = std::chrono::milliseconds(1000);


        app.init_Entity_withRunAwayStatus(entities, entity, runaway_waittime);

        WHEN("emit removeRunAway-Event") {
            app.emit_event<gameevent::CreatureRemoveRunAwayEvent>(entity);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("runAway is removed") {
                    CHECK_FALSE(earr::enum_array_at(
                        life.hasstatus, +data::CreatureStatus::RunAway));
                }
            }
        }
    }
}


SCENARIO("Creature Entity with RunAway Status then "
         "runAway-Timer is stoped") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusRunAwaySystemApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto& timers =
            entities.get<gamecomp::CreatureProgressTimersComponent>(entity);


        auto runaway_waittime = std::chrono::milliseconds(1000);

        auto& runaway_timer = earr::enum_array_at(
            timers.timer, +gamecomp::CreatureProgressTimer::RunAway);
        gamecomp::ProgressTimer& runaway_progresstimer = runaway_timer;

        app.init_Entity_withRunAwayStatus(entities, entity, runaway_waittime);

        WHEN("emit removeRunAway-Event") {
            app.emit_event<gameevent::CreatureRemoveRunAwayEvent>(entity);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("runAway-Timer is stoped") {
                    CHECK_FALSE(runaway_progresstimer.timer.isstart);
                }
            }
        }
    }
}
