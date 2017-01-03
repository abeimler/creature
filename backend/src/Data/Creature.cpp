#include "Data/Creature.h"

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
        this->genderdistribution_[i] = [&]() {
            auto index = CreatureGender::_from_integral_nothrow(i);

            if (index) {
                if (*index != +CreatureGender::None &&
                    *index != +CreatureGender::Hermaphrodite) {
                    return 100.0 / (this->genderdistribution_.size() - 2.0);
                }
            }

            return 0.0;
        }();
    }
}

Creature::Creature(Battler battler) : Battler(std::move(battler)) {
    for (size_t i = 0; i < this->genderdistribution_.size(); i++) {
        this->genderdistribution_[i] = [&]() {
            auto index = CreatureGender::_from_integral_nothrow(i);

            if (index) {
                if (*index != +CreatureGender::None &&
                    *index != +CreatureGender::Hermaphrodite) {
                    return 100.0 / (this->genderdistribution_.size() - 2.0);
                }
            }

            return 0.0;
        }();
    }
}

CreatureStarter::CreatureStarter(const Creature& creature) {
    this->setCreature(creature);
}

} // namespace data
