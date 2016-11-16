#include "Entity/Data/DataManager.h"



namespace gameentity {


CreatureDataManager::CreatureDataManager() : DataManagerBase(findDataByName) {}


CreatureBattlerStatusDataManager::CreatureBattlerStatusDataManager()
    : DataManagerBase(findDataByName) {}


CreatureRootTypeDataManager::CreatureRootTypeDataManager()
    : DataManagerBase(findDataByName) {}


ElementDataManager::ElementDataManager() : DataManagerBase(findDataByName) {}


FoodDataManager::FoodDataManager() : DataManagerBase(findDataByName) {}

SkillDataManager::SkillDataManager() : DataManagerBase(findDataByName) {}

CreatureStarterDataManager::CreatureStarterDataManager()
    : DataManagerBase(findDataByName) {}
} // namespace gameentity