#ifndef DATA_CREATUREANIMATIONIMAGE_HPP_
#define DATA_CREATUREANIMATIONIMAGE_HPP_

#include "Data/Basic.hpp"

#include "Data/Creature.hpp"

namespace data {

/// Creature Animation Graphic
class CreatureAnimationImage {

    private:
    std::string creature_name_;

    std::string image_filename_;
    std::string plist_filename_;

    public:
    CreatureAnimationImage() = default;

    /// Creature
    std::string getCreatureName() const { return this->creature_name_; }

    /// Animation-Sprite für Normal,Status,Misc und Battler Animation
    std::string getAnimationImageFilename() const {
        return this->image_filename_;
    }

    /**
     * Animation-Sprites-plist für Normal,Status,Misc
     * und Battler Animation
     */
    std::string getAnimationPListFilename() const {
        return this->plist_filename_;
    }

    void setCreature(const Creature& creature) {
        this->creature_name_ = creature.getName();
    }

    void seteAnimationImageFilename(std::string filename) {
        this->image_filename_ = filename;
    }

    void setAnimationPListFilename(std::string filename) {
        this->plist_filename_ = filename;
    }
};
} // namespace data

#endif // DATA_CREATUREANIMATIONIMAGE_HPP_