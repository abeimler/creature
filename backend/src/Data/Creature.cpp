#include "Data/Creature.h"

#include "util.h"

namespace data {

EvolutionCondition::EvolutionCondition() {
    earr::enum_array_fill(this->attr_, 0);
    earr::enum_array_fill(this->traintime_, true);
}

void EvolutionCondition::setTrainTimeEveryDay() {
    earr::enum_array_fill(this->traintime_, true);
}


void Creature::initGenderDistribution() {
    for (size_t i = 0; i < this->genderdistribution_.size(); i++) {
        this->genderdistribution_[i] = [&]() -> int {
            auto index = CreatureGender::_from_integral_nothrow(i);

            if (index) {
                if (*index != +CreatureGender::None &&
                    *index != +CreatureGender::Hermaphrodite) {
                        const auto excluded_genderdistribution_size = (this->genderdistribution_.size() > 2)? this->genderdistribution_.size()-2 : this->genderdistribution_.size();
                        
                        return 100 / excluded_genderdistribution_size;
                }
            }

            return 0;
        }();
    }
}

Creature::Creature() {
    initGenderDistribution();
}

Creature::Creature(Battler battler) : Battler(std::move(battler)) {
    initGenderDistribution();
}

CreatureStarter::CreatureStarter(const Creature& creature) {
    this->setCreature(creature);
}

} // namespace data
