#include "Application/GameApplication.h"

namespace game {

GameApplication::GameApplication() { this->initSystems(); }

void GameApplication::initSystems() {
    this->makeListener<gamesystem::CreatureAddStatusSystem,
                       gameevent::CreatureAddStatusEvent>(this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerAddBattlerStatusSystem,
                       gameevent::CreatureAddBattlerStatusEvent>(
        this->datamanager_);

    this->makeListener<gamesystem::CreatureBattlerCreatureRecoverSystem,
                       gameevent::CreatureRecoverEvent>();
    this->makeListener<gamesystem::CreatureBattlerCreatureAddExpSystem,
                       gameevent::CreatureAddExpEvent>();

    this->makeListener<gamesystem::CreatureRemoveStatusSystem,
                       gameevent::CreatureRemoveStatusEvent>(
        this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerRemoveBattlerStatusSystem,
                       gameevent::CreatureRemoveBattlerStatusEvent>(
        this->datamanager_);

    this->makeSystem<gamesystem::CreatureBattlerSystem>(this->datamanager_);

    this->makeSystem<gamesystem::CreatureProgressTimerSystem>();

    this->makeListener<gamesystem::CreatureDeadSystem,
                       gameevent::CreatureMakeDeadEvent>();
    this->makeListener<gamesystem::CreatureMakeRunAwaySystem,
                       gameevent::CreatureMakeRunAwayEvent>();
    this->makeListener<gamesystem::CreatureRemoveRunAwaySystem,
                       gameevent::CreatureRemoveRunAwayEvent>();
                       
    this->makeSystem<gamesystem::CreatureSystem>(this->datamanager_);

    this->makeSystem<gamesystem::CreatureDigestionSystem>();
    this->makeListener<gamesystem::CreatureDigestionCallbackSystem, 
                       gameevent::ProgressTimerCallbackEvent>();
}

} // namespace gamesystem