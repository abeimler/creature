#ifndef DATA_CREATUREIMAGE_HPP_
#define DATA_CREATUREIMAGE_HPP_

#include "Data/Basic.hpp"

#include "Data/Creature.hpp"

namespace data {

class CreatureImage {
    private:
    std::string creature_name_;

    std::string filename_;

    public:
    CreatureImage() = default;

    std::string getCreatureName() const { return this->creature_name_; }

    std::string getFilename() const { return this->filename_; }

    void setCreature(const Creature& creature) {
        this->creature_name_ = creature.getName();
    }

    void setFilename(std::string filename) { this->filename_ = filename; }
};

} // namespace data

#endif // DATA_CREATUREIMAGE_HPP_
