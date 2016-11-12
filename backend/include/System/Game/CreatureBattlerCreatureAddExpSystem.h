#ifndef SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_


#include "basic.h"

#include "Data/Basic.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerCreatureAddExpSystem : public Listener<gameevent::CreatureAddExpEvent> {
    public:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    CreatureBattlerCreatureAddExpSystem() = default;

    void update(const gameevent::CreatureAddExpEvent& event, EntityManager& entities, EventBus& events, TimeDelta dt) override;

};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_
