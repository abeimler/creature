#ifndef DATA_BATTLERSTATUS_H_
#define DATA_BATTLERSTATUS_H_

#include "Data/Basic.h"

#include "Data/Element.h"

namespace data {


///  BattlerStatus Restriction (order by smallest effect (first))
BETTER_ENUM(StatusRestrictionOption, size_t, None,
            BEGIN = None, ///< None
            AtkEnemies,   ///< allways attack enemies
            AtkAllies,    ///< allways attack allies
            AtkAll,       ///< allways attack enemies/allies
            NoMove,       ///< can't move
            NoMoveEvade,  ///< can't move or evade
            END)

/// BattlerStatus Option
BETTER_ENUM(StatusOption, size_t, EvadePhysical,
            BEGIN = EvadePhysical, ///< can't hit by physical attacks
            ReflectSkills,         ///< Skill reflected back to the user
            Dead,                  ///< dead/knockout
            END)


///  BattlerStatus Extent (trigger to remove BattlerStatus)
class StatusExtent {
    private:
    option_t afterbattle_ = false;
    option_t bydamage_ = false;
    turns_t turn_ = 0u;
    percent_rate_t rate_ = 30;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("afterbattle", afterbattle_));
        ar(cereal::make_nvp("bydamage", bydamage_));
        ar(cereal::make_nvp("turn", turn_));
        ar(cereal::make_nvp("rate", rate_));
    }

    public:
    StatusExtent() = default;

    option_t isAfterBattle() const { return this->afterbattle_; }
    option_t isByDamage() const { return this->bydamage_; }
    turns_t getTurn() const { return this->turn_; }
    percent_rate_t getRate() const { return this->rate_; }

    void setAfterBattle(option_t afterbattle) { this->afterbattle_ = afterbattle; }
    void setByDamage(option_t bydamage) { this->bydamage_ = bydamage; }
    void setTurn(turns_t turn) { this->turn_ = turn; }
    void setRate(percent_rate_t rate) { this->rate_ = rate; }
};

/// Damange by BattlerStatus
class StatusDamage {
    private:
    damage_t value_ = 0;
    option_t ispercent_ = false;

    damage_t damageperstep_ = 0;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("value", value_));
        ar(cereal::make_nvp("ispercent", ispercent_));
        ar(cereal::make_nvp("damageperstep", damageperstep_));
    }


    public:
    StatusDamage() = default;

    /// Damage value (< 0 => heal)
    damage_t getValue() const { return this->value_; }

    /// true, damagevalue is in percent
    option_t isPercent() const { return this->ispercent_; }

    /// damage on Field/Map per Step (0 = no damage)
    damage_t getDamagePerSteps() const { return this->damageperstep_; }

    void setValue(damage_t value) { this->value_ = value; }

    void isPercent(option_t percent) { this->ispercent_ = percent; }

    void setDamagePerSteps(damage_t damageperstep) {
        this->damageperstep_ = damageperstep;
    }
};

/// BattlerStatus
class BattlerStatus {
    std::string name_;
    priority_t priority_ = 0;

    earr::enum_array<Attribute, attr_factor_t> attr_factor_;

    StatusExtent extent_;

    /// Resist of Element (index => Element Name)
    /// @todo element_id als index machen
    std::unordered_map<std::string, Resist> elementresist_;

    /// BattlerStatus to cancel/remove
    /// @note dont add itself, forbidden BattlerStatusID of itself (endless
    /// loop)
    std::vector<std::string> removestatuses_;

    noskill_t noskillatk_ = -1;
    noskill_t noskillint_ = -1;


    factor_rate_t hitrate_ = 1.0;
    factor_rate_t critical_hitrate_ = 1.0;
    factor_rate_t evarate_ = 1.0;

    StatusDamage hpdamage_;
    StatusDamage mpdamage_;
    StatusRestrictionOption restriction_ = StatusRestrictionOption::None;
    earr::enum_array<StatusOption, option_t> option_;
    earr::enum_array<Resist, sensitivity_t> sensitivity_;


    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("name", name_));
        ar(cereal::make_nvp("attr_factor", attr_factor_));
        ar(cereal::make_nvp("priority", priority_));

        ar(cereal::make_nvp("extent", extent_));

        ar(cereal::make_nvp("elementresist", elementresist_));
        ar(cereal::make_nvp("removestatuses", removestatuses_));

        ar(cereal::make_nvp("noskillatk", noskillatk_));
        ar(cereal::make_nvp("noskillint", noskillint_));

        ar(cereal::make_nvp("hitrate", hitrate_));
        ar(cereal::make_nvp("critical_hitrate", critical_hitrate_));
        ar(cereal::make_nvp("evarate", evarate_));

        ar(cereal::make_nvp("hpdamage", hpdamage_));
        ar(cereal::make_nvp("mpdamage", mpdamage_));
        ar(cereal::make_nvp("restriction", restriction_));
        ar(cereal::make_nvp("option", option_));
        ar(cereal::make_nvp("sensitivity", sensitivity_));
    }



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
    const earr::enum_array<Attribute, attr_factor_t>& getAttrFactor() const {
        return this->attr_factor_;
    }

    /**
     * @param attr Attribute
     * @return Attribute Boni
     */
    attr_factor_t getAttrFactor(Attribute attr) const {
        return earr::enum_array_at(this->attr_factor_, attr);
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

        return (it != this->elementresist_.end()) ? it->second
                                                  : +Resist::Normal;
    }

    Resist getElementResist(const Element& element) const {
        return this->getElementResist(element.getName());
    }

    /// removed BattlerStatuses
    const std::vector<std::string>& getRemoveStatuses() const {
        return this->removestatuses_;
    }

    /// skills with X atk or more can't be use (disabled = -1)
    noskill_t getNoSkillATK() const { return this->noskillatk_; }

    /// skills with X int or more can't be use (disabled = -1)
    noskill_t getNoSkillINT() const { return this->noskillint_; }

    /// BattlerStatus priority
    priority_t getPriority() const { return this->priority_; }

    /// Boni HitRate factor
    factor_rate_t getHitRate() const { return this->hitrate_; }

    /// Boni Critical HitRate factor
    factor_rate_t getCriticalHitRate() const { return this->critical_hitrate_; }

    /// Boni EvaRate factor
    factor_rate_t getEvaRate() const { return this->evarate_; }

    /// HP damage
    const StatusDamage& getHPDamage() const { return this->hpdamage_; }

    /// MP damage
    const StatusDamage& getMPDamage() const { return this->mpdamage_; }

    /// BattlerStatus Options
    const earr::enum_array<StatusOption, option_t>& getOption() const {
        return this->option_;
    }

    /**
     * @param p_option BattlerStatus Option
     * @brief BattlerStatus Option
     */
    option_t getOption(StatusOption p_option) const {
        return earr::enum_array_at(this->option_, p_option);
    }

    /// BattlerStatus restriction
    StatusRestrictionOption getRestriction() const {
        return this->restriction_;
    }

    /// BattlerStatus sensitivity (Resist value)
    const earr::enum_array<Resist, sensitivity_t>& getSensitivity() const {
        return this->sensitivity_;
    }

    /**
     * @param resist Resist
     * @return BattlerStatus sensitivity (Resist value)
     */
    sensitivity_t getSensitivity(Resist resist) const {
        return earr::enum_array_at(this->sensitivity_, resist);
    }

    void setName(std::string name) { this->name_ = name; }

    void setAttrFactor(const earr::enum_array<Attribute, attr_factor_t>& attr) {
        this->attr_factor_ = attr;
    }

    void setAttrFactor(Attribute attr, attr_factor_t value) {
        earr::enum_array_set(this->attr_factor_, attr, value);
    }

    void setExtent(const StatusExtent& extent) { this->extent_ = extent; }

    void setElementResist(const Element& element, Resist resist) {
        this->elementresist_[element.getName()] = resist;
    }

    void addRemoveStatus(const BattlerStatus& status) {
        this->removestatuses_.push_back(status.getName());
    }

    void clearRemoveStatuses() { this->removestatuses_.clear(); }

    void setNoSkillATK(noskill_t value) { this->noskillatk_ = value; }

    void setNoSkillINT(noskill_t value) { this->noskillint_ = value; }

    void setPriority(priority_t priority) { this->priority_ = priority; }

    void setHitRate(factor_rate_t hitrate) { this->hitrate_ = hitrate; }

    void setCriticalHitRate(factor_rate_t critical_hitrate) {
        this->critical_hitrate_ = critical_hitrate;
    }

    void setEvaRate(factor_rate_t evarate) { this->evarate_ = evarate; }

    void setHPDamage(const StatusDamage& damage) { this->hpdamage_ = damage; }

    void setMPDamage(const StatusDamage& damage) { this->mpdamage_ = damage; }

    /**
     * @param option BattlerStatus options
     * @brief set BattlerStatus options
     */
    void setOption(const earr::enum_array<StatusOption, option_t>& option) {
        this->option_ = option;
    }

    /**
     * @param option BattlerStatus option
     * @param active BattlerStatus option on/off
     * @brief set BattlerStatus option
     */
    void setOption(StatusOption option, option_t active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setRestriction(StatusRestrictionOption restriction) {
        this->restriction_ = restriction;
    }

    void setSensitivity(const earr::enum_array<Resist, sensitivity_t>& sensitivity) {
        this->sensitivity_ = sensitivity;
    }

    /**
     * @param resist resist
     * @param value Resist value
     * @brief set BattlerStatus resist value
     */
    void setSensitivity(Resist resist, sensitivity_t value) {
        earr::enum_array_set(this->sensitivity_, resist, value);
    }

    /**
     * @param name BattlerStatus Name
     * @return removed BattlerStatus
     * @return remove_statuses.end(), BattlerStatus not removed
     */
    decltype(auto) findRemoveStatus(std::string name) {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return name == battlerstatus_name;
        };

        return std::find_if(std::begin(this->removestatuses_),
                            std::end(this->removestatuses_), find_byName);
    }

    decltype(auto) findRemoveStatus(const BattlerStatus& battlerstatus) {
        return this->findRemoveStatus(battlerstatus.getName());
    }
};
} // namespace data

#endif // DATA_BATTLERSTATUS_H_
