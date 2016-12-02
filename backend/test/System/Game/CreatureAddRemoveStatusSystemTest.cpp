#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureAddStatusSystem.h"
#include "System/Game/CreatureBattlerAddBattlerStatusSystem.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusSystem.h"
#include "System/Game/CreatureRemoveStatusSystem.h"
#include "System/Game/CreatureSystem.h"


class CreatureAddRemoveStatusSystemApplication : public gamesystem::Application {
    private:

    std::vector<data::CreatureBattlerStatus>
    getCreatureStatusList() {
        /*
            Normal = BEGIN, ///< Normal Status (no Statuses)
            Dead,           ///< Dead
            RunAway,        ///< Run Away
            Sleep,          ///< Sleep
            InHospital,     ///< In Hospital
            RestInHospital, ///< Rest in Hospital
            Rest,           ///< Rest
            Hurt,           ///< Hurt
            Ill,            ///< Ill
            Training,       ///< In Training
            Unhappy,        ///< Unhappy
            Happy,          ///< Happy
            Hungry,         ///< Hungry
            Thirsty,        ///< Thirsty
            Replete,        ///< Replete
            Tired,          ///< Tired
        */

        std::vector<data::CreatureBattlerStatus> statuses;

        data::CreatureBattlerStatus dead ("Dead", data::CreatureStatus::Dead);
        dead.setPriority(100);
        statuses.push_back(dead);

        data::CreatureBattlerStatus runaway ("RunAway", data::CreatureStatus::RunAway);
        runaway.setPriority(95);
        statuses.push_back(runaway);

        data::CreatureBattlerStatus sleep ("Sleep", data::CreatureStatus::Sleep);
        sleep.setPriority(90);
        statuses.push_back(sleep);

        data::CreatureBattlerStatus inhospital ("InHospital", data::CreatureStatus::InHospital);
        inhospital.setPriority(85);
        statuses.push_back(inhospital);

        data::CreatureBattlerStatus restinhospital ("RestInHospital", data::CreatureStatus::RestInHospital);
        restinhospital.setPriority(90);
        statuses.push_back(restinhospital);

        data::CreatureBattlerStatus rest ("Rest", data::CreatureStatus::Rest);
        rest.setPriority(85);
        statuses.push_back(rest);

        data::CreatureBattlerStatus hurt ("Hurt", data::CreatureStatus::Hurt);
        hurt.setPriority(85);
        statuses.push_back(hurt);

        data::CreatureBattlerStatus ill ("Ill", data::CreatureStatus::Ill);
        ill.setPriority(85);
        statuses.push_back(ill);

        data::CreatureBattlerStatus training ("Training", data::CreatureStatus::Training);
        training.setPriority(85);
        statuses.push_back(training);

        data::CreatureBattlerStatus unhappy ("Unhappy", data::CreatureStatus::Unhappy);
        unhappy.setPriority(70);
        statuses.push_back(unhappy);

        data::CreatureBattlerStatus happy ("Happy", data::CreatureStatus::Happy);
        happy.setPriority(70);
        statuses.push_back(happy);

        data::CreatureBattlerStatus hungry (HUNGRY_STATUS_NAME, data::CreatureStatus::Hungry);
        hungry.setPriority(80);
        statuses.push_back(hungry);

        data::CreatureBattlerStatus thirsty ("Thirsty", data::CreatureStatus::Thirsty);
        thirsty.setPriority(80);
        statuses.push_back(thirsty);

        data::CreatureBattlerStatus replete ("Replete", data::CreatureStatus::Replete);
        replete.setPriority(70);
        statuses.push_back(replete);

        data::CreatureBattlerStatus tired ("Tired", data::CreatureStatus::Tired);
        tired.setPriority(80);
        statuses.push_back(tired);

        return statuses;
    }

    void init_DataManager_AllCreatureStatuses(gameentity::DataManager& p_datamanager){
        auto statuses = getCreatureStatusList();
        for(const auto& status : statuses) {
            p_datamanager.saveCreatureBattlerStatus(status);
        }
    }

    public:
    const char* HUNGRY_STATUS_NAME = "Hungry";

    gameentity::DataManager datamanager;

    std::shared_ptr<gamesystem::CreatureAddStatusSystem> creatureAddStatusSystem;
    std::shared_ptr<gamesystem::CreatureRemoveStatusSystem> creatureRemoveStatusSystem;
    std::shared_ptr<gamesystem::CreatureBattlerAddBattlerStatusSystem> creatureBattlerAddBattlerStatusSystem;
    std::shared_ptr<gamesystem::CreatureBattlerRemoveBattlerStatusSystem> creatureBattlerRemoveBattlerStatusSystem;
    std::shared_ptr<gamesystem::CreatureSystem> creatureSystem;

    CreatureAddRemoveStatusSystemApplication() {
        init_DataManager_AllCreatureStatuses(datamanager);

        this->creatureAddStatusSystem =
            std::make_shared<gamesystem::CreatureAddStatusSystem>(
                this->datamanager);
        this->creatureRemoveStatusSystem =
            std::make_shared<gamesystem::CreatureRemoveStatusSystem>(
                this->datamanager);
        this->creatureBattlerAddBattlerStatusSystem =
            std::make_shared<gamesystem::CreatureBattlerAddBattlerStatusSystem>(
                this->datamanager);
        this->creatureBattlerRemoveBattlerStatusSystem =
            std::make_shared<gamesystem::CreatureBattlerRemoveBattlerStatusSystem>(
                this->datamanager);
        this->creatureSystem =
            std::make_shared<gamesystem::CreatureSystem>(
                this->datamanager);

        this->addListener<gameevent::CreatureAddStatusEvent>(this->creatureAddStatusSystem);
        this->addListener<gameevent::CreatureRemoveStatusEvent>(this->creatureRemoveStatusSystem);
        this->addListener<gameevent::CreatureAddBattlerStatusEvent>(this->creatureBattlerAddBattlerStatusSystem);
        this->addListener<gameevent::CreatureRemoveBattlerStatusEvent>(this->creatureBattlerRemoveBattlerStatusSystem);
        this->addSystem(this->creatureSystem);
    }



    void init_Entity_withHungryStatus(gameentity::Entity entity) {
        gamecomputil::ProgressTimerUtil progresstimer_util;

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

    void
    init_Entity_withStartedRunAwayTimer(gameentity::Entity entity,
                                        gamecomp::waittime_t waittime) {
        CreatureTestData creatureTestData;
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto& runawayunhappy_timer = earr::enum_array_at(timers->callback,
            +gamecomp::CreatureProgressTimerCallback::RunAwayUnhappy);
        gamecomp::ProgressTimer& runawayunhappy_progresstimer =
            runawayunhappy_timer.base;

        auto time = creatureTestData.make_time_point_01_01_2000();
        progresstimer_util.init(runawayunhappy_progresstimer, time, 1.0f);
        runawayunhappy_progresstimer.waittime.fill(waittime);
        progresstimer_util.start(runawayunhappy_progresstimer);

        auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        psyche->luck = 0;

        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        life->causeofrunaway = gamecomp::CauseOfRunAway::Unhappy;
    }

    void init_Entity_withCanGoSleepTired(gameentity::Entity entity) {
        CreatureTestData creatureTestData;
        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& tired_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Tired);
        gamecomp::ProgressTimer& tired_progresstimer = tired_timer;
        tired_progresstimer.value = creatureTestData.CANGOSLEEP_AT_TIRED;
    }

    void init_Entity_withOneHPMP(gameentity::Entity entity) {
        gamecomputil::ProgressTimerUtil progresstimer_util;

        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        creature_battler->hp = 1;
        creature_battler->mp = 1;
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity emit addStatus-Event Hungry to set "
         "status Hungry") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusSystemApplication app;
        auto& entities = app.getEntityManager();

        auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        WHEN("emit addStatus-Event Hungry") {
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, +data::CreatureStatus::Hungry);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);
                //app.update(app.FAKE_TIMEDELTA);

                THEN("has hungry status") {
                    CHECK(earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Hungry));
                }

                THEN("battler statuses is not empty") {
                    REQUIRE_FALSE(battlerstatuses->statuses_name.empty());

                    auto& status_name = battlerstatuses->statuses_name.front();

                    AND_THEN("battler status is hungry") {
                        CHECK(app.HUNGRY_STATUS_NAME == status_name);
                    }
                }
            }
        }
    }
}
