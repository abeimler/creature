#ifndef SYSTEM_GAME_CREATUREBATTLERCREATUREREMOVESTATUSLISTENER_H_
#define SYSTEM_GAME_CREATUREBATTLERCREATUREREMOVESTATUSLISTENER_H_


#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureBattlerRemoveBattlerStatusListener
    : public Listener<gameevent::CreatureRemoveBattlerStatusEvent> {
    private:
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;

    public:
    CreatureBattlerRemoveBattlerStatusListener(gameentity::DataManager& datamanager);

    void sortBattlerStatuses(std::vector<std::string>& statuses_name);

    void removeBattlerStatus(
        const gameevent::CreatureRemoveBattlerStatusEvent& event,
        Component<gamecomp::BattlerStatusesComponent>& battlerstatuses);
    void removeStartBattlerStatusTurn(
        const gameevent::CreatureRemoveBattlerStatusEvent& event,
        Component<gamecomp::BattlerStatusesComponent>& battlerstatuses);
        
    void update(const gameevent::CreatureRemoveBattlerStatusEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;
};


} // namespace gamesystem

#endif // SYSTEM_GAME_CREATUREBATTLERCREATUREREMOVESTATUSLISTENER_H_
