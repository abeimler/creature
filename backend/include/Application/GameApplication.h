#ifndef APPLICATION_GAMEAPPLICATION_H_
#define APPLICATION_GAMEAPPLICATION_H_

#include "basic.h"

#include "Entity/Data/DataManager.h"
#include "System/Application.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "System/Game/CreatureAddStatusSystem.h"
#include "System/Game/CreatureBattlerAddBattlerStatusSystem.h"
#include "System/Game/CreatureBattlerCreatureAddExpSystem.h"
#include "System/Game/CreatureBattlerCreatureRecoverSystem.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusSystem.h"
#include "System/Game/CreatureBattlerSystem.h"
#include "System/Game/CreatureDeadSystem.h"
#include "System/Game/CreatureDoNotingSystem.h"
#include "System/Game/CreatureProgressTimerSystem.h"
#include "System/Game/CreatureRemoveStatusSystem.h"
#include "System/Game/CreatureRunAwaySystem.h"
#include "System/Game/CreatureSystem.h"


namespace game {

class GameApplication : public gamesystem::Application {
    private:
    gameentity::CreatureEntityCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;
    gameentity::DataManager datamanager_;

    void initSystems();

    public:

    GameApplication();

    gameentity::DataManager& getDataManager() { return this->datamanager_; }
    const gameentity::DataManager& getDataManager() const { return this->datamanager_; }

    gameentity::CreatureBattlerCreator& getCreatureBattlerCreator() { return this->creaturebattler_creator_; }
    const gameentity::CreatureBattlerCreator& getCreatureBattlerCreator() const { return this->creaturebattler_creator_; }
    
    gameentity::CreatureEntityCreator& getCreatureEntityCreator() { return this->creaturecreator_; }
    const gameentity::CreatureEntityCreator& getCreatureEntityCreator() const { return this->creaturecreator_; }
};

} // namespace gamesystem


#endif // APPLICATION_GAMEAPPLICATION_H_
