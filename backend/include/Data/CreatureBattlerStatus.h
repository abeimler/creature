#ifndef DATA_CREATUREBATTLERSTATUS_H_
#define DATA_CREATUREBATTLERSTATUS_H_

#include "Data/Basic.h"

#include "Data/BattlerStatus.h"
#include "Data/Creature.h"

namespace data {

/// Creature BattlerStatus
class CreatureBattlerStatus : public BattlerStatus {
    private:
    CreatureStatus creaturestatus_ = CreatureStatus::Normal;
    std::string filename_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("_base", cereal::base_class<BattlerStatus>(this)));

        ar(cereal::make_nvp("creaturestatus", creaturestatus_));
        ar(cereal::make_nvp("filename", filename_));
    }



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

#endif // DATA_CREATUREBATTLERSTATUS_H_
