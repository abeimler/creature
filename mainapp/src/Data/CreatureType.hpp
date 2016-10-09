#ifndef DATA_CREATURETYPE_HPP_
#define DATA_CREATURETYPE_HPP_

#include "Data/Basic.hpp"

namespace data {

/// Creature Type (sub Creature Type of Creature Root Type)
class CreatureType {
    private:
    /// Typename
    std::string name_;

    std::string creatureroottype_name_;

    public:
    CreatureType() = default;

    explicit CreatureType(std::string name);

    /// name
    std::string getName() const { return this->name_; }

    /**
     * @param name name
     * @brief set name
     */
    void setName(std::string name) { this->name_ = name; }

    std::string getCreatureRootType() const {
        return this->creatureroottype_name_;
    }

    void setCreatureRootType(const std::string& roottype) {
        this->creatureroottype_name_ = roottype;
    }
};

class CreatureRootType {
    private:
    std::string name_;

    std::vector<CreatureType> types_;

    public:
    CreatureRootType() = default;

    explicit CreatureRootType(std::string name);

    /// name
    std::string getName() const { return this->name_; }

    /// sub type
    const std::vector<CreatureType>& getTypes() const { return this->types_; }

    void setName(std::string name) { this->name_ = name; }

    void addCreatureType(const CreatureType& type) {
        this->types_.push_back(type);
        auto& newtype = this->types_.back();
        newtype.setCreatureRootType(this->name_);
    }

    void removeCreatureType(std::string name) {
        auto find_byName = [name](const CreatureType& type) {
            return name == type.getName();
        };

        this->types_.erase(std::remove_if(std::begin(this->types_),
                                          std::end(this->types_), find_byName),
                           std::end(this->types_));
    }
};

} // namespace data

#endif // DATA_CREATURETYPE_HPP_
