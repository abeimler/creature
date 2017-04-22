#include <thread>

#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureAddStatusListener.h"
#include "System/Game/CreatureBattlerAddBattlerStatusListener.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusListener.h"
#include "System/Game/CreatureMakeDeadListener.h"
#include "System/Game/CreatureProgressTimerSystem.h"
#include "System/Game/CreatureRemoveStatusListener.h"
#include "System/Game/CreatureSystem.h"


class CreatureAddRemoveStatusDeadSystemApplication
    : public gamesystem::Application {
    private:
    std::vector<data::CreatureBattlerStatus> getCreatureStatusList() {
        std::vector<data::CreatureBattlerStatus> statuses;

        data::CreatureBattlerStatus dead(DEAD_STATUS_NAME,
                                         data::CreatureStatus::Dead);
        dead.setPriority(100);
        dead.setOption(data::StatusOption::Dead, true);
        statuses.push_back(dead);

        data::CreatureBattlerStatus runaway("RunAway",
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
    const char* DEAD_STATUS_NAME = "Dead";

    gameentity::DataManager datamanager;

    std::shared_ptr<gamesystem::CreatureAddStatusListener>
        creatureAddStatusListener;
    std::shared_ptr<gamesystem::CreatureRemoveStatusListener>
        creatureRemoveStatusListener;
    std::shared_ptr<gamesystem::CreatureBattlerAddBattlerStatusListener>
        creatureBattlerAddBattlerStatusListener;
    std::shared_ptr<gamesystem::CreatureBattlerRemoveBattlerStatusListener>
        creatureBattlerRemoveBattlerStatusListener;

    std::shared_ptr<gamesystem::CreatureProgressTimerSystem>
        creatureProgressTimerSystem;
    std::shared_ptr<gamesystem::CreatureSystem> creatureSystem;
    std::shared_ptr<gamesystem::CreatureMakeDeadListener>
        creatureMakeDeadListener;

    CreatureAddRemoveStatusDeadSystemApplication() {
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

        this->creatureProgressTimerSystem =
            std::make_shared<gamesystem::CreatureProgressTimerSystem>();
        this->creatureSystem =
            std::make_shared<gamesystem::CreatureSystem>(this->datamanager);
        this->creatureMakeDeadListener =
            std::make_shared<gamesystem::CreatureMakeDeadListener>();

        this->addSystem(this->creatureProgressTimerSystem);
        this->addSystem(this->creatureSystem);
        this->addListener(this->creatureMakeDeadListener);
        this->addListener(this->creatureAddStatusListener);
        this->addListener(this->creatureRemoveStatusListener);
        this->addListener(this->creatureBattlerAddBattlerStatusListener);
        this->addListener(this->creatureBattlerRemoveBattlerStatusListener);
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
        battlerstatuses.statuses_name.emplace_back(HUNGRY_STATUS_NAME);
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
      CreatureTestData creatureTestData{};
      gamecomputil::ProgressTimerUtil progresstimer_util{};

      auto &timers =
          entities.get<gamecomp::CreatureProgressTimersComponent>(entity);
      auto &runawayunhappy_timer = earr::enum_array_at(
          timers.callback,
          +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy);
      gamecomp::ProgressTimer &runawayunhappy_progresstimer =
          runawayunhappy_timer.base;

      auto time = creatureTestData.make_time_point_01_01_2000();
      progresstimer_util.init(runawayunhappy_progresstimer, time, 1.0f);
      runawayunhappy_progresstimer.waittime.fill(waittime);
      progresstimer_util.start(runawayunhappy_progresstimer);

      auto &psyche = entities.get<gamecomp::CreaturePsycheComponent>(entity);
      psyche.luck = 0;

      auto &life = entities.get<gamecomp::CreatureLifeComponent>(entity);
      life.causeofrunaway = gamecomp::CauseOfRunAway::Unhappy;
    }

    void init_Entity_withCanGoSleepTired(gameentity::EntityManager& entities, gameentity::Entity entity) {
      CreatureTestData creatureTestData{};
      auto &timers =
          entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

      gamecomp::ProgressTimer &tired_timer = earr::enum_array_at(
          timers.timer, +gamecomp::CreatureProgressTimer::Tired);
      gamecomp::ProgressTimer &tired_progresstimer = tired_timer;
      tired_progresstimer.value = creatureTestData.CANGOSLEEP_AT_TIRED;
    }

    void init_Entity_withOneHPMP(gameentity::EntityManager& entities, gameentity::Entity entity) {
        // gamecomputil::ProgressTimerUtil progresstimer_util;

        auto& creature_battler =
            entities.get<gamecomp::CreatureBattlerComponent>(entity);

        creature_battler.hp = 1;
        creature_battler.mp = 1;
    }

    void init_Entity_withStartedLifeTimer(gameentity::EntityManager& entities, gameentity::Entity entity) {
      CreatureTestData creatureTestData{};
      computil::DateTimerUtil datetimer_util_{};

      auto &timers =
          entities.get<gamecomp::CreatureProgressTimersComponent>(entity);

      auto time = creatureTestData.make_time_point_01_01_2000();
      datetimer_util_.init(timers.lifetimer, time, 1.0f);
      datetimer_util_.start(timers.lifetimer);
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity with small maxlifetime when life to long then die") {
    GIVEN("Creature Entity with small maxlifetime") {
      CreatureTestData creatureTestData{};
      CreatureAddRemoveStatusDeadSystemApplication app;
      auto &entities = app.getEntityManager();

      // auto time = creatureTestData.make_time_point_01_01_2000();
      auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

      // auto timers =
      // entity.component<gamecomp::CreatureProgressTimersComponent>();
      // auto battlerstatuses =
      // entity.component<gamecomp::BattlerStatusesComponent>();
      auto &life = entities.get<gamecomp::CreatureLifeComponent>(entity);
      // auto bodlystate =
      // entity.component<gamecomp::CreatureBodilyStateComponent>();

      app.init_Entity_withStartedLifeTimer(entities, entity);

      auto waittime = std::chrono::milliseconds(100);
      life.maxlifetime = std::chrono::milliseconds(50);

      WHEN("update manager") {
        std::this_thread::sleep_for(waittime);
        app.update(app.FAKE_TIMEDELTA);

        THEN("is dead") { CHECK(life.isdead); }
        }
    }
}

SCENARIO("Creature Entity with zero hp to make dead with updateLifeAttribute") {
    GIVEN("Creature Entity with new attrplus value") {
      CreatureTestData creatureTestData{};
      CreatureAddRemoveStatusDeadSystemApplication app;
      auto &entities = app.getEntityManager();

      // auto time = creatureTestData.make_time_point_01_01_2000();
      auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

      // auto timers =
      // entity.component<gamecomp::CreatureProgressTimersComponent>();
      // auto battlerstatuses =
      // entity.component<gamecomp::BattlerStatusesComponent>();
      auto &life = entities.get<gamecomp::CreatureLifeComponent>(entity);
      // auto bodlystate =
      // entity.component<gamecomp::CreatureBodilyStateComponent>();
      // auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
      // auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
      auto &creature_battler =
          entities.get<gamecomp::CreatureBattlerComponent>(entity);

      life.inbattle = false;
      creature_battler.hp = 0;

      WHEN("update manager") {
        app.update(app.FAKE_TIMEDELTA);

        THEN("is dead") { CHECK(life.isdead); }
        }
    }
}