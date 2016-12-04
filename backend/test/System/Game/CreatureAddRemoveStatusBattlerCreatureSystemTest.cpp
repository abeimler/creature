#include <thread>

#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureAddStatusSystem.h"
#include "System/Game/CreatureBattlerAddBattlerStatusSystem.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusSystem.h"
#include "System/Game/CreatureRemoveStatusSystem.h"
#include "System/Game/CreatureSystem.h"
#include "System/Game/CreatureBattlerSystem.h"
#include "System/Game/CreatureProgressTimerSystem.h"


class CreatureAddRemoveStatusBattlerCreatureSystemApplication : public gamesystem::Application {
    private:

    std::vector<data::CreatureBattlerStatus>
    getCreatureStatusList() {
        std::vector<data::CreatureBattlerStatus> statuses;

        data::CreatureBattlerStatus dead ("Dead", data::CreatureStatus::Dead);
        dead.setPriority(100);
        dead.setOption(data::StatusOption::Dead, true);
        statuses.push_back(dead);

        data::CreatureBattlerStatus runaway ("RunAway", data::CreatureStatus::RunAway);
        runaway.setPriority(95);
        statuses.push_back(runaway);

        data::CreatureBattlerStatus sleep (SLEEP_STATUS_NAME, data::CreatureStatus::Sleep);
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

        data::CreatureBattlerStatus ill (ILL_STATUS_NAME, data::CreatureStatus::Ill);
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
    const char* SLEEP_STATUS_NAME = "Sleep";
    const char* ILL_STATUS_NAME = "Ill";

    gameentity::DataManager datamanager;

    std::shared_ptr<gamesystem::CreatureAddStatusSystem> creatureAddStatusSystem;
    std::shared_ptr<gamesystem::CreatureRemoveStatusSystem> creatureRemoveStatusSystem;
    std::shared_ptr<gamesystem::CreatureBattlerAddBattlerStatusSystem> creatureBattlerAddBattlerStatusSystem;
    std::shared_ptr<gamesystem::CreatureBattlerRemoveBattlerStatusSystem> creatureBattlerRemoveBattlerStatusSystem;
    std::shared_ptr<gamesystem::CreatureBattlerSystem> creatureBattlerSystem;
    std::shared_ptr<gamesystem::CreatureProgressTimerSystem> creatureProgressTimerSystem;
    std::shared_ptr<gamesystem::CreatureSystem> creatureSystem;

    CreatureAddRemoveStatusBattlerCreatureSystemApplication() {
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
        this->creatureProgressTimerSystem =
                std::make_shared<gamesystem::CreatureProgressTimerSystem>();
        this->creatureSystem =
            std::make_shared<gamesystem::CreatureSystem>(
                this->datamanager);
        this->creatureBattlerSystem =
            std::make_shared<gamesystem::CreatureBattlerSystem>(
                this->datamanager);

        this->addListener<gameevent::CreatureAddStatusEvent>(this->creatureAddStatusSystem);
        this->addListener<gameevent::CreatureRemoveStatusEvent>(this->creatureRemoveStatusSystem);
        this->addListener<gameevent::CreatureAddBattlerStatusEvent>(this->creatureBattlerAddBattlerStatusSystem);
        this->addListener<gameevent::CreatureRemoveBattlerStatusEvent>(this->creatureBattlerRemoveBattlerStatusSystem);
        
        this->addSystem(this->creatureBattlerSystem);
        this->addSystem(this->creatureProgressTimerSystem);
        this->addSystem(this->creatureSystem);
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

    void init_Entity_withSleepStatus(gameentity::Entity entity) {
        //gamecomputil::ProgressTimerUtil progresstimer_util;

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        gamecomp::ProgressTimer& tired_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Tired);

        tired_timer.value = 100.0f;
        tired_timer.isfull = true;

        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Sleep) = true;

        auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        battlerstatuses->statuses_name.push_back(SLEEP_STATUS_NAME);
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
        //gamecomputil::ProgressTimerUtil progresstimer_util;

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
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
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


SCENARIO("Creature Entity emit same addStatus-Event in wrong order then order "
         "statuses") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        WHEN("emit some addStatus-Events") {
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, data::CreatureStatus::Hungry);
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, data::CreatureStatus::Ill);
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, data::CreatureStatus::Sleep);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);
                //app.update(app.FAKE_TIMEDELTA);
                //app.update(app.FAKE_TIMEDELTA);

                THEN("has hungry status") {
                    CHECK(earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Hungry));
                }

                THEN("has sleep status") {
                    CHECK(earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Sleep));
                }

                THEN("has ill status") {
                    CHECK(earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Ill));
                }

                THEN("battler statuses is not empty") {
                    REQUIRE(battlerstatuses->statuses_name.size() >= 3);

                    auto& first_status_name = battlerstatuses->statuses_name.at(0);
                    auto& second_status_name = battlerstatuses->statuses_name.at(1);
                    auto& third_status_name = battlerstatuses->statuses_name.at(2);

                    AND_THEN("1. battler status is sleep") {
                        CHECK(app.SLEEP_STATUS_NAME == first_status_name);
                    }

                    AND_THEN("2. battler status is ill") {
                        CHECK(app.ILL_STATUS_NAME == second_status_name);
                    }

                    AND_THEN("3. battler status is hungry") {
                        CHECK(app.HUNGRY_STATUS_NAME == third_status_name);
                    }
                }
            }
        }
    }
}





SCENARIO("Creature Entity with Hungry status and emit removeStatus-Event "
         "Hungry to remove "
         "Hungry status") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        app.init_Entity_withHungryStatus(entity);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();

        WHEN("emit removeStatus-Event Hungry") {
            app.emit_event<gameevent::CreatureRemoveStatusEvent>(entity, data::CreatureStatus::Hungry);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);
                //app.update(app.FAKE_TIMEDELTA);
                //app.update(app.FAKE_TIMEDELTA);

                THEN("has not hungry status") {
                    CHECK_FALSE(earr::enum_array_at(life->hasstatus, 
                        +data::CreatureStatus::Hungry));
                }
            }
        }
    }
}


SCENARIO("Creature Entity emit addStatus-Event Ill to increment ill-Counter") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();

        WHEN("emit addStatus-Event Ill") {
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, data::CreatureStatus::Ill);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("ill-Counter is set") {
                    CHECK(bodlystate->illcount > 0);
                }
            }
        }
    }
}

SCENARIO("Creature Entity emit addStatus-Event Hurt to increment hurt-Counter") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();

        WHEN("emit addStatus-Event Hurt") {
            app.emit_event<gameevent::CreatureAddStatusEvent>(entity, data::CreatureStatus::Hurt);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                THEN("hurt-Counter is set") {
                    CHECK(bodlystate->hurtcount > 0);
                }
            }
        }
    }
}


SCENARIO("Creature Entity with tired to can go sleep") {
    GIVEN("Creature Entity with enough tired for sleep") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        auto sleep = entity.component<gamecomp::CreatureSleepComponent>();

        app.init_Entity_isNotBusy(entity);
        app.init_Entity_withCanGoSleepTired(entity);

        sleep->cangosleep = false;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("can go sleep") { 
                CHECK(sleep->cangosleep); 
            }
        }
    }
}


SCENARIO("Creature Entity with negative psyche values then clamp it with "
         "updatePsycheValues") {
    GIVEN("Creature Entity with negative psyche values") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();

        psyche->disc = -1;
        psyche->luck = -1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp disc to min 0") {
                CHECK(psyche->disc >= 0.0);
            }

            THEN("clamp luck to min 0") {
                CHECK(psyche->luck >= 0.0);
            }
        }
    }
}


SCENARIO("Creature Entity with big psyche values then clamp it with "
         "updatePsycheValues") {
    GIVEN("Creature Entity with negative psyche values") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();

        psyche->disc = 101;
        psyche->luck = 101;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp disc to max 100") {
                CHECK(psyche->disc <= 100);
            }

            THEN("clamp luck to max 100") {
                CHECK(psyche->luck <= 100);
            }
        }
    }
}


SCENARIO("Creature Entity with to big lvl then clamp it with "
         "updateCreatureBattlerAttribute") {
    GIVEN("Creature Entity with to big lvl") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        creature_battler->lvl = creatureTestData.MAXLEVEL + 1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp lvl to max") {
                REQUIRE(creature_battler->lvl == creatureTestData.MAXLEVEL);
            }
        }
    }
}



SCENARIO("Creature Entity with to small lvl then clamp it with "
         "updateCreatureBattlerAttribute") {
    GIVEN("Creature Entity with to big lvl") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        creature_battler->lvl = creatureTestData.MINLEVEL - 1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp lvl to min") {
                REQUIRE(creature_battler->lvl == creatureTestData.MINLEVEL);
            }
        }
    }
}

SCENARIO("Creature Entity with new attrplus value then update attr with "
         "updateCreatureBattlerAttribute") {
    GIVEN("Creature Entity with new attrplus value") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        earr::enum_array_at(creature_battler->attrplus,
                                +data::Attribute::MaxHP) = 1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("new attr value is set") {
                CHECK(earr::enum_array_at(creature_battler->attr, +data::Attribute::MaxHP) > creatureTestData.MAXHP);
            }
        }
    }
}


SCENARIO("Creature Entity with overmax hp mp then clamp hp mp value with "
         "updateCreatureBattlerAttribute") {
    GIVEN("Creature Entity with new attrplus value") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        creature_battler->hp = creatureTestData.MAXHP + 1;
        creature_battler->mp = creatureTestData.MAXMP + 1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp hp to max") {
                CHECK(creature_battler->hp == creatureTestData.MAXHP);
            }

            THEN("clamp mp to max") {
                CHECK(creature_battler->mp == creatureTestData.MAXMP);
            }
        }
    }
}

SCENARIO("Creature Entity with negative hp mp then clamp hp mp value with "
         "updateCreatureBattlerAttribute") {
    GIVEN("Creature Entity with new attrplus value") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        // auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        creature_battler->hp = -1;
        creature_battler->mp = -1;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("clamp hp to min") {
                CHECK(creature_battler->hp == 0);
            }

            THEN("clamp mp to min") {
                CHECK(creature_battler->mp == 0);
            }
        }
    }
}


SCENARIO("Creature Entity update createlevel in timers") {
    GIVEN("Creature Entity with none updated creaturelevel") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        //auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        //auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        timers->creaturelevel = data::CreatureLevel::Egg;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("timers.creaturelevel is set") {
                REQUIRE(timers->creaturelevel == creatureTestData.CREATURELEVEL);
            }
        }
    }
}


SCENARIO("Creature Entity update needrefreshin") {
    GIVEN("Creature Entity with none updated creaturelevel") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        //auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        timers->creaturelevel = data::CreatureLevel::Egg;

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            THEN("needrefreshin is set") {
                REQUIRE(life->needrefreshin >
                        std::chrono::milliseconds::zero());
            }
        }
    }
}


SCENARIO("Creature Entity with Sleep to set tired factor negative") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;
        CreatureAddRemoveStatusBattlerCreatureSystemApplication app;
        auto& entities = app.getEntityManager();

        //auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto timers = entity.component<gamecomp::CreatureProgressTimersComponent>();
        //auto battlerstatuses = entity.component<gamecomp::BattlerStatusesComponent>();
        auto life = entity.component<gamecomp::CreatureLifeComponent>();
        //auto bodlystate = entity.component<gamecomp::CreatureBodilyStateComponent>();
        //auto sleep = entity.component<gamecomp::CreatureSleepComponent>();
        //auto psyche = entity.component<gamecomp::CreaturePsycheComponent>();
        //auto creature_battler = entity.component<gamecomp::CreatureBattlerComponent>();

        auto& tired_timer = earr::enum_array_at(timers->timer, 
            +gamecomp::CreatureProgressTimer::Tired);
        gamecomp::ProgressTimer& tired_progresstimer = tired_timer;

        app.init_Entity_withSleepStatus(entity);

        WHEN("update manager") {
            app.update(app.FAKE_TIMEDELTA);

            REQUIRE(earr::enum_array_at(life->hasstatus, +data::CreatureStatus::Sleep));

            THEN("tired factor is negative") {
                REQUIRE(tired_progresstimer.factor < 0.0f);
            }
        }
    }
}