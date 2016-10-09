#include "CreatureBattlerStatus.hpp"

namespace data {

CreatureBattlerStatus::CreatureBattlerStatus(const BattlerStatus& battlerstatus,
                                             CreatureStatus status)
    : BattlerStatus(battlerstatus), creaturestatus_(status) {}

CreatureBattlerStatus::CreatureBattlerStatus(std::string name,
                                             CreatureStatus status)
    : BattlerStatus(name), creaturestatus_(status) {}

} // namespace data
