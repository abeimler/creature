#include "doctest.h"

#include "System/Application.h"

#include "System/Game/MakeCreatureHelper.h"

#include "System/Game/CreatureBattlerCreatureRecoverListener.h"

class RecoverEventListenerMockup
    : public gamesystem::Listener<gameevent::CreatureRecoverEvent> {
    public:
    bool emitevent = false;

    RecoverEventListenerMockup() = default;

    void update(const gameevent::CreatureRecoverEvent& /*event*/,
                EntityManager& /*entities*/, EventBus& /*events*/,
                TimeDelta /*dt*/) override {
        this->emitevent = true;
    }
};

class CreatureBattlerCreatureRecoverSystemApplication
    : public gamesystem::Application {
    public:
    std::shared_ptr<RecoverEventListenerMockup> eventlistenermockup;
    std::shared_ptr<gamesystem::CreatureBattlerCreatureRecoverListener>
        creatureBattlerCreatureRecoverListener;

    CreatureBattlerCreatureRecoverSystemApplication() {
        this->eventlistenermockup =
            std::make_shared<RecoverEventListenerMockup>();
        this->creatureBattlerCreatureRecoverListener = std::make_shared<
            gamesystem::CreatureBattlerCreatureRecoverListener>();

        this->addListener(this->eventlistenermockup);
        this->addListener(this->creatureBattlerCreatureRecoverListener);
    }


    void init_Entity_withLowHPMP(gameentity::EntityManager& entities, gameentity::Entity entity) {
        auto& creature_battler =
            entities.get<gamecomp::CreatureBattlerComponent>(entity);

        creature_battler.hp = 1;
        creature_battler.mp = 1;
    }

    static constexpr gamesystem::TimeDelta FAKE_TIMEDELTA = 1.0 / 60;
};



SCENARIO(
    "Creature Entity with low hp mp when emit recover-Event then heal hp mp") {
    GIVEN("Creature Entity") {
      CreatureTestData creatureTestData{};

      CreatureBattlerCreatureRecoverSystemApplication app;
      auto &entities = app.getEntityManager();

      // auto time = creatureTestData.make_time_point_01_01_2000();
      auto entity = MakeCreatureHelper::create_Entity_Creature(entities);

      app.init_Entity_withLowHPMP(entities, entity);

      auto &creature_battler =
          entities.get<gamecomp::CreatureBattlerComponent>(entity);

      WHEN("emit recover-Event") {
        app.emit_event<gameevent::CreatureRecoverEvent>(entity);

        AND_WHEN("update entities") {
          app.update(app.FAKE_TIMEDELTA);

          REQUIRE(app.eventlistenermockup->emitevent);

          THEN("hp is recover") {
            CHECK(creature_battler.hp == creatureTestData.MAXHP);
          }

          THEN("mp is recover") {
            CHECK(creature_battler.mp == creatureTestData.MAXMP);
          }
        }
        }
    }
}
