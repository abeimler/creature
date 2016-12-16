#include "Application/GameApplication.h"

namespace game {

GameApplication::GameApplication() { this->initSystems(); }

void GameApplication::initSystems() {
    this->makeListener<gamesystem::CreatureMakeDeadListener>();
    this->makeListener<gamesystem::CreatureMakeRunAwayListener>();
    this->makeListener<gamesystem::CreatureRemoveRunAwayListener>();

    this->makeListener<gamesystem::CreatureAddStatusListener>(
        this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerAddBattlerStatusListener>(
        this->datamanager_);

    this->makeListener<gamesystem::CreatureRemoveStatusListener>(
        this->datamanager_);
    this->makeListener<gamesystem::CreatureBattlerRemoveBattlerStatusListener>(
        this->datamanager_);


    this->makeListener<gamesystem::CreatureBattlerCreatureRecoverListener>();
    this->makeListener<gamesystem::CreatureBattlerCreatureAddExpListener>();
    this->makeSystem<gamesystem::CreatureBattlerSystem>(this->datamanager_);

    this->makeSystem<gamesystem::CreatureProgressTimerSystem>();

    this->makeSystem<gamesystem::CreatureSystem>(this->datamanager_);

    this->makeListener<gamesystem::CreatureDigestionCallbackListener>();
    this->makeSystem<gamesystem::CreatureDigestionSystem>();


    this->makeListener<gamesystem::CreatureTryToEvolveListener>(this->datamanager_);
}

} // namespace gamesystem