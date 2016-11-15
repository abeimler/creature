#include "Data/CreatureBattlerStatus.h"

namespace data {

CreatureBattlerStatus::CreatureBattlerStatus(BattlerStatus  battlerstatus,
                                             CreatureStatus status)
    : BattlerStatus(std::move(battlerstatus)), creaturestatus_(std::move(status)) {}

CreatureBattlerStatus::CreatureBattlerStatus(std::string name,
                                             CreatureStatus status)
    : BattlerStatus(name), creaturestatus_(std::move(status)) {}

} // namespace data
