#include "Data/Battler.h"

namespace data {

LearnSkill::LearnSkill(lvl_t lvl, const Skill& skill)
    : lvl_(lvl), skill_name_(skill.getName()) {}

Battler::Battler() {
    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attrbasis_, 0);
    earr::enum_array_fill(this->attrinflation_, 0);
}

} // namespace data
