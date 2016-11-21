#include "Application/GameApplication.h"

namespace game {

GameApplication::GameApplication() {
    this->initSystems();
}

void GameApplication::initSystems() {
    this->makeListener<gamesystem::CreatureAddStatusSystem, gameevent::CreatureAddStatusEvent>(this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerAddBattlerStatusSystem, gameevent::CreatureAddBattlerStatusEvent>(this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerCreatureRecoverSystem, gameevent::CreatureRecoverEvent>();
    this->makeListener<gamesystem::CreatureBattlerCreatureAddExpSystem, gameevent::CreatureAddExpEvent>();
    this->makeListener<gamesystem::CreatureRemoveStatusSystem, gameevent::CreatureRemoveStatusEvent>(this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerRemoveBattlerStatusSystem, gameevent::CreatureRemoveBattlerStatusEvent>(this->datamanager_);
    
    this->makeSystem<gamesystem::CreatureBattlerSystem>(this->datamanager_);
    this->makeListener<gamesystem::CreatureDeadSystem, gameevent::CreatureMakeDeadEvent>(this->datamanager_);
    this->makeListener<gamesystem::CreatureRunAwaySystem, gameevent::CreatureMakeRunAwayEvent>(this->datamanager_);
    this->makeSystem<gamesystem::CreatureProgressTimerSystem>();
    this->makeSystem<gamesystem::CreatureSystem>(this->datamanager_);
}

} // namespace gamesystem