#ifndef DATA_CREATUREBATTLERSTATUS_HPP_
#define DATA_CREATUREBATTLERSTATUS_HPP_

#include "Data/Basic.hpp"

#include "Data/BattlerStatus.hpp"
#include "Data/Creature.hpp"

namespace data {

/// Creature BattlerStatus
class CreatureBattlerStatus : public BattlerStatus {
    private:
    CreatureStatus creaturestatus_ = CreatureStatus::Normal;
    std::string filename_;

    public:
    CreatureBattlerStatus() = default;

    CreatureBattlerStatus(const BattlerStatus& battlerstatus,
                          CreatureStatus status);

    CreatureBattlerStatus(std::string name, CreatureStatus status);

    /// Creature Status
    CreatureStatus getCreatureStatus() const { return this->creaturestatus_; }

    /// filename/url of icon
    std::string getFilename() const { return this->filename_; }

    void setCreatureStatus(CreatureStatus status) {
        this->creaturestatus_ = status;
    }

    void setFilename(std::string filename) { this->filename_ = filename; }
};
} // namespace data

#endif // DATA_CREATUREBATTLERSTATUS_HPP_
