#ifndef SYSTEM_GAME_CREATUREBATTLERCREATUREADDSTATUSLISTENER_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATUREADDSTATUSLISTENER_H_


#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerAddBattlerStatusListener
    : public Listener<gameevent::CreatureAddBattlerStatusEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;

    void sortBattlerStatuses(std::vector<std::string>& statuses_name);

    public:
    CreatureBattlerAddBattlerStatusListener(gameentity::DataManager& datamanager);

    void update(const gameevent::CreatureAddBattlerStatusEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATUREADDSTATUSLISTENER_H_
