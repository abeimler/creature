#include "BattlerStatus.hpp"

namespace data {

BattlerStatus::BattlerStatus() {
    const int start_resist = 90;
    for (size_t i = 0; i < this->sensitivity_.size(); i++) {
        this->sensitivity_[i] =
            (i > 0) ? this->sensitivity_[i - 1] * 100 / 90 : start_resist;
    }

    earr::enum_array_fill(this->option_, false);
    earr::enum_array_fill(this->attr_, 1.0f);
}

BattlerStatus::BattlerStatus(std::string name) : BattlerStatus() {
    this->name_ = name;
}

void BattlerStatus::genResistValues() {
    int start_resist = util::random(80, 90);
    for (size_t i = 0; i < this->sensitivity_.size(); i++) {
        this->sensitivity_[i] =
            (i > 0) ? this->sensitivity_[i - 1] * 100 / util::random(85, 90)
                    : start_resist;
    }
}
} // namespace data
