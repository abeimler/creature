#ifndef DATA_CREATUREIMAGE_H_
#define DATA_CREATUREIMAGE_H_

#include "Data/Basic.h"

#include "Data/Creature.h"

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

#endif // DATA_CREATUREIMAGE_H_
