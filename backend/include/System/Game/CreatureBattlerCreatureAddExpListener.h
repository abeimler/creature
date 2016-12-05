#ifndef SYSTEM_GAME_CREATUREBATTLERCREATUREADDEXPLISTENER_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATUREADDEXPLISTENER_H_


#include "basic.h"

#include "Data/Basic.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerCreatureAddExpListener
    : public Listener<gameevent::CreatureAddExpEvent> {
    public:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    CreatureBattlerCreatureAddExpListener() = default;

    void addExp(gamecomp::CreatureDataComponent& creature_data,
                gamecomp::CreatureBattlerComponent& creature_battler,
                data::attr_t add_exp);

    void update(const gameevent::CreatureAddExpEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATUREADDEXPLISTENER_H_
