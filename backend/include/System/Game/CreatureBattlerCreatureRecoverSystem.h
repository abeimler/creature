#ifndef SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_


#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerCreatureRecoverSystem : public Listener<gameevent::CreatureRecoverEvent> {
    public:

    CreatureBattlerCreatureRecoverSystem() = default;

    void update(const gameevent::CreatureRecoverEvent& event, EntityManager& entities, EventBus& events, TimeDelta dt) override;

};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERSYSTEM_H_
