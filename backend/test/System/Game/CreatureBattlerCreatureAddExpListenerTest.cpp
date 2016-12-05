#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureBattlerCreatureAddExpListener.h"

class AddExpEventListenerMockup
    : public gamesystem::Listener<gameevent::CreatureAddExpEvent> {
    public:
    bool emitevent = false;

    AddExpEventListenerMockup() = default;

    void update(const gameevent::CreatureAddExpEvent& /*event*/,
                EntityManager& /*entities*/, EventBus& /*events*/,
                TimeDelta /*dt*/) override {
        this->emitevent = true;
    }
};

class CreatureBattlerCreatureAddExpListenerApplication
    : public gamesystem::Application {
    public:
    std::shared_ptr<AddExpEventListenerMockup> eventlistenermockup;
    std::shared_ptr<gamesystem::CreatureBattlerCreatureAddExpListener> creatureBattlerCreatureAddExpListener;

    CreatureBattlerCreatureAddExpListenerApplication() {
        this->eventlistenermockup = std::make_shared<AddExpEventListenerMockup>();
        this->creatureBattlerCreatureAddExpListener = std::make_shared<gamesystem::CreatureBattlerCreatureAddExpListener>();

        this->addListener(this->eventlistenermockup);
        this->addListener(this->creatureBattlerCreatureAddExpListener);
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO("Creature Entity emit addExp-Event to gain exp") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerCreatureAddExpListenerApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        int add_exp = 1;

        WHEN("emit addExp-Event") {
            app.emit_event<gameevent::CreatureAddExpEvent>(entity, add_exp);

            AND_WHEN("update manager") {
                app.update(app.FAKE_TIMEDELTA);

                REQUIRE(app.eventlistenermockup->emitevent);

                THEN("has gain exp") { CHECK(creature_battler->exp > 0); }
            }
        }
    }
}

SCENARIO("Creature Entity emit addExp-Event to level up") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerCreatureAddExpListenerApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        int old_current_lvl = creatureTestData.LVL;
        int add_exp = creatureTestData.EXP;

        WHEN("emit addExp-Event") {
            app.emit_event<gameevent::CreatureAddExpEvent>(entity, add_exp);

            AND_WHEN("update entities") {
                app.update(app.FAKE_TIMEDELTA);

                REQUIRE(app.eventlistenermockup->emitevent);

                THEN("has gain exp") { CHECK(creature_battler->exp > 0); }

                THEN("has level up") {
                    CHECK(creature_battler->lvl > old_current_lvl);
                }
            }
        }
    }
}

SCENARIO(
    "Creature Entity emit addExp-Event to has Attributes go up") {
    GIVEN("Creature Entity") {
        CreatureTestData creatureTestData;

        CreatureBattlerCreatureAddExpListenerApplication app;
        auto& entities = app.getEntityManager();

        // auto time = creatureTestData.make_time_point_01_01_2000();
        auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

        auto creature_battler =
            entity.component<gamecomp::CreatureBattlerComponent>();

        //int old_current_lvl = creatureTestData.LVL;
        int old_current_maxhp = creatureTestData.MAXHP;
        int old_current_maxmp = creatureTestData.MAXMP;
        int add_exp = creatureTestData.EXP;

        WHEN("emit addExp-Event") {
            app.emit_event<gameevent::CreatureAddExpEvent>(entity, add_exp);

            AND_WHEN("update entities") {
                app.update(app.FAKE_TIMEDELTA);

                REQUIRE(app.eventlistenermockup->emitevent);



                THEN("MaxHP Attributes has up") {
                    CHECK(earr::enum_array_at(creature_battler->attr,
                                              +data::Attribute::MaxHP) >
                          old_current_maxhp);
                }

                THEN("MaxMP Attributes has up") {
                    CHECK(earr::enum_array_at(creature_battler->attr,
                                              +data::Attribute::MaxMP) >
                          old_current_maxmp);
                }
            }
        }
    }
}
