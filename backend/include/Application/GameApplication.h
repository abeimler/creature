#ifndef APPLICATION_GAMEAPPLICATION_H_
#define APPLICATION_GAMEAPPLICATION_H_

#include "basic.h"

#include "Entity/Data/DataManager.h"
#include "System/Application.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "System/Game/CreatureAddStatusListener.h"
#include "System/Game/CreatureBattlerAddBattlerStatusListener.h"
#include "System/Game/CreatureBattlerCreatureAddExpListener.h"
#include "System/Game/CreatureBattlerCreatureRecoverListener.h"
#include "System/Game/CreatureBattlerRemoveBattlerStatusListener.h"
#include "System/Game/CreatureBattlerSystem.h"
#include "System/Game/CreatureMakeDeadListener.h"
#include "System/Game/CreatureDigestionCallbackListener.h"
#include "System/Game/CreatureDigestionSystem.h"
#include "System/Game/CreatureDoNotingSystem.h"
#include "System/Game/CreatureProgressTimerSystem.h"
#include "System/Game/CreatureRemoveStatusListener.h"
#include "System/Game/CreatureMakeRunAwayListener.h"
#include "System/Game/CreatureRemoveRunAwayListener.h"
#include "System/Game/CreatureSystem.h"
#include "System/Game/CreatureTryToEvolveListener.h"


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
