#include "Creature.h"

namespace data {

EvolutionCondition::EvolutionCondition() {
    earr::enum_array_fill(this->attr_, 0);
    earr::enum_array_fill(this->traintime_, true);
}

void EvolutionCondition::setTrainTimeEveryDay() {
    earr::enum_array_fill(this->traintime_, true);
}

Creature::Creature() {
    for (size_t i = 0; i < this->genderdistribution_.size(); i++) {
        this->genderdistribution_[i] = 0.0;

        CreatureGender index = static_cast<CreatureGender>(i);

        if (index != CreatureGender::None &&
            index != CreatureGender::Hermaphrodite) {
            this->genderdistribution_[i] =
                100 / (this->genderdistribution_.size() - 2);
        }
    }
}

Creature::Creature(const Battler& battler) : Battler(battler) {
    for (size_t i = 0; i < this->genderdistribution_.size(); i++) {
        this->genderdistribution_[i] = 0.0;

        CreatureGender index = static_cast<CreatureGender>(i);

        if (index != CreatureGender::None &&
            index != CreatureGender::Hermaphrodite) {
            this->genderdistribution_[i] =
                100 / (this->genderdistribution_.size() - 2);
        }
    }
}

} // namespace data
