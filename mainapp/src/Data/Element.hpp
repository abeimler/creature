#ifndef DATA_CREATURE_ELEMENT_HPP_
#define DATA_CREATURE_ELEMENT_HPP_

#include "Data/Basic.hpp"

namespace data {

/// Element for Skill, Attack, Weapons, ...
class Element {
    private:
    std::string name_;

    public:
    Element() = default;

    explicit Element(std::string name);

    /// name
    std::string getName() const { return this->name_; }

    void setName(std::string name) { this->name_ = name; }
};

} // namespace data

#endif // DATA_CREATURE_ELEMENT_HPP_
