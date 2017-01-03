#ifndef SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERLISTENER_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERLISTENER_H_


#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerCreatureRecoverListener
    : public Listener<gameevent::CreatureRecoverEvent> {
    public:
    CreatureBattlerCreatureRecoverListener() = default;

    void recover(gamecomp::CreatureBattlerComponent& creature_battler);

    void update(const gameevent::CreatureRecoverEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATURERECOVERLISTENER_H_
