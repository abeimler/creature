#ifndef DATA_BATTLERSTATUS_H_
#define DATA_BATTLERSTATUS_H_

#include "Data/Basic.h"

#include "Data/Element.h"

namespace data {

///  BattlerStatus Restriction (order by smallest effect (first))
enum class StatusRestrictionOption : size_t {
    BEGIN,
    None = BEGIN, ///< None
    AtkEnemies,   ///< allways attack enemies
    AtkAllies,    ///< allways attack allies
    AtkAll,       ///< allways attack enemies/allies
    NoMove,       ///< can't move
    NoMoveEvade,  ///< can't move or evade
    END
};

/// BattlerStatus Option
enum class StatusOption : size_t {
    BEGIN,
    EvadePhysical = BEGIN, ///< can't hit by physical attacks
    ReflectSkills,         ///< Skill reflected back to the user
    Dead,                  ///< dead/knockout
    END
};

///  BattlerStatus Extent (trigger to remove BattlerStatus)
class StatusExtent {
    private:
    bool afterbattle_ = false;
    bool bydamage_ = false;
    int turn_ = 0;
    int rate_ = 30;

    public:
    StatusExtent() = default;

    bool isAfterBattle() const { return this->afterbattle_; }
    bool isByDamage() const { return this->bydamage_; }
    int getTurn() const { return this->turn_; }
    int getRate() const { return this->rate_; }

    void setAfterBattle(bool afterbattle) { this->afterbattle_ = afterbattle; }
    void setByDamage(bool bydamage) { this->bydamage_ = bydamage; }
    void setTurn(bool turn) { this->turn_ = turn; }
    void setRate(int rate) { this->rate_ = rate; }
};

/// Damange by BattlerStatus
class StatusDamage {
    private:
    int value_ = 0;
    bool ispercent_ = 0;

    int damageperstep_ = false;

    public:
    StatusDamage() = default;

    /// Damage value (< 0 => heal)
    int getValue() const { return this->value_; }

    /// true, damagevalue is in percent
    bool isPercent() const { return this->ispercent_; }

    /// damage on Field/Map per Step (0 = no damage)
    int getDamagePerSteps() const { return this->damageperstep_; }

    void setValue(int value) { this->value_ = value; }

    void isPercent(bool percent) { this->ispercent_ = percent; }

    void setDamagePerSteps(int damageperstep) {
        this->damageperstep_ = damageperstep;
    }
};

/// BattlerStatus
class BattlerStatus {
    std::string name_;

    earr::enum_array<Attribute, float> attr_;

    StatusExtent extent_;

    /// Resist of Element (index => Element Name)
    /// @todo element_id als index machen
    std::unordered_map<std::string, Resist> elementresist_;

    /// BattlerStatus to cancel/remove
    /// @note dont add itself, forbidden BattlerStatusID of itself (endless
    /// loop)
    std::vector<std::string> removestatuses_;

    int noskillatk_ = -1;
    int noskillint_ = -1;

    int priority_ = 0;

    double hitrate_ = 1.0;
    StatusDamage hpdamage_;
    StatusDamage mpdamage_;
    StatusRestrictionOption restriction_ = StatusRestrictionOption::None;
    earr::enum_array<StatusOption, bool> option_;
    earr::enum_array<Resist, int> sensitivity_;

    public:
    BattlerStatus();

    virtual ~BattlerStatus() = default;
    BattlerStatus(const BattlerStatus&) = default;
    BattlerStatus& operator=(const BattlerStatus&) = default;
    BattlerStatus(BattlerStatus&&) = default;
    BattlerStatus& operator=(BattlerStatus&&) = default;

    explicit BattlerStatus(std::string name);

    /// sort by priority and BattlerStatusID
    inline bool operator<(const BattlerStatus& obj) const {
        return this->priority_ < obj.priority_;
    }

    /// sort by priority and BattlerStatusID
    inline bool operator>(const BattlerStatus& obj) const {
        return this->priority_ > obj.priority_;
    }

    /// generate random ResistValues
    void genResistValues();

    /// BattlerStatus name
    std::string getName() const { return this->name_; }

    /// Attribute Boni
    const earr::enum_array<Attribute, float>& getAttr() const {
        return this->attr_;
    }

    /**
     * @param attr Attribute
     * @return Attribute Boni
     */
    float getAttr(Attribute attr) const {
        return earr::enum_array_at(this->attr_, attr);
    }

    /// BattlerStatus extent (remove condition)
    const StatusExtent& getExtent() const { return this->extent_; }

    /// Resist of Elements
    const std::unordered_map<std::string, Resist>& getElementResist() const {
        return this->elementresist_;
    }

    /**
     * @param element_id ElementID
     * @return Resist of Element
     */
    Resist getElementResist(std::string element_name) const {
        auto it = this->elementresist_.find(element_name);

        return (it != this->elementresist_.end()) ? it->second : Resist::Normal;
    }

    Resist getElementResist(const Element& element) const {
        return this->getElementResist(element.getName());
    }

    /// removed BattlerStatuses
    const std::vector<std::string>& getRemoveStatuses() const {
        return this->removestatuses_;
    }

    /// skills with X atk or more can't be use (disabled = -1)
    int getNoSkillATK() const { return this->noskillatk_; }

    /// skills with X int or more can't be use (disabled = -1)
    int getNoSkillINT() const { return this->noskillint_; }

    /// BattlerStatus priority
    int getPriority() const { return this->priority_; }

    /// Boni HitRate factor
    double getHitRate() const { return this->hitrate_; }

    /// HP damage
    const StatusDamage& getHPDamage() const { return this->hpdamage_; }

    /// MP damage
    const StatusDamage& getMPDamage() const { return this->mpdamage_; }

    /// BattlerStatus Options
    const earr::enum_array<StatusOption, bool>& getOption() const {
        return this->option_;
    }

    /**
     * @param p_option BattlerStatus Option
     * @brief BattlerStatus Option
     */
    bool getOption(StatusOption p_option) const {
        return earr::enum_array_at(this->option_, p_option);
    }

    /// BattlerStatus restriction
    StatusRestrictionOption getRestriction() const {
        return this->restriction_;
    }

    /// BattlerStatus sensitivity (Resist value)
    const earr::enum_array<Resist, int>& getSensitivity() const {
        return this->sensitivity_;
    }

    /**
     * @param resist Resist
     * @return BattlerStatus sensitivity (Resist value)
     */
    int getSensitivity(Resist resist) const {
        return earr::enum_array_at(this->sensitivity_, resist);
    }

    void setName(std::string name) { this->name_ = name; }

    void setAttr(const earr::enum_array<Attribute, float>& attr) {
        this->attr_ = attr;
    }

    void setAttr(Attribute attr, float value) {
        earr::enum_array_set(this->attr_, attr, value);
    }

    void setExtent(const StatusExtent& extent) { this->extent_ = extent; }

    void setElementResist(const std::shared_ptr<Element>& element,
                          Resist resist) {
        if (!element) {
            return;
        }

        this->elementresist_[element->getName()] = resist;
    }

    void setRemoveStatuses(const std::vector<std::string>& statuses) {
        this->removestatuses_ = statuses;
    }

    void setNoSkillATK(int value) { this->noskillatk_ = value; }

    void setNoSkillINT(int value) { this->noskillint_ = value; }

    void setPriority(int priority) { this->priority_ = priority; }

    void setHitRate(double hitrate) { this->hitrate_ = hitrate; }

    void setHPDamage(const StatusDamage& damage) { this->hpdamage_ = damage; }

    void setMPDamage(const StatusDamage& damage) { this->mpdamage_ = damage; }

    /**
     * @param option BattlerStatus options
     * @brief set BattlerStatus options
     */
    void setOption(const earr::enum_array<StatusOption, bool>& option) {
        this->option_ = option;
    }

    /**
     * @param option BattlerStatus option
     * @param active BattlerStatus option on/off
     * @brief set BattlerStatus option
     */
    void setOption(StatusOption option, bool active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setRestriction(StatusRestrictionOption restriction) {
        this->restriction_ = restriction;
    }

    void setSensitivity(const earr::enum_array<Resist, int>& sensitivity) {
        this->sensitivity_ = sensitivity;
    }

    /**
     * @param resist resist
     * @param value Resist value
     * @brief set BattlerStatus resist value
     */
    void setSensitivity(Resist resist, int value) {
        earr::enum_array_set(this->sensitivity_, resist, value);
    }

    /**
     * @param name BattlerStatus Name
     * @return removed BattlerStatus
     * @return remove_statuses.end(), BattlerStatus not removed
     */
    decltype(auto) getRemoveStatus(std::string name) {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return name == battlerstatus_name;
        };

        return std::find_if(std::begin(this->removestatuses_),
                            std::end(this->removestatuses_), find_byName);
    }

    decltype(auto) getRemoveStatus(const BattlerStatus& battlerstatus) {
        return this->getRemoveStatus(battlerstatus.getName());
    }
};
} // namespace data

#endif // DATA_BATTLERSTATUS_H_
