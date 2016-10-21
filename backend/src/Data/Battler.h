#ifndef DATA_BATTLER_H_
#define DATA_BATTLER_H_

#include "Data/Basic.h"

#include "Data/Element.h"
#include "Data/Skill.h"

namespace data {

/// Weapon Animation: Move
BETTER_ENUM(ActionPrevMoveOption, size_t, BEGIN,
            None = BEGIN, ///< none
            StepForward,  ///< 1 step forward
            StepBackward, ///< 1 Step backward
            JumpForward,  ///< 1 jump forward
            JumpBackward, ///< 1 jump backward
            MovetoTarget, ///< move to target
            END)

/// Batter Animation Pose
BETTER_ENUM(AnimationPose, size_t, BEGIN,
            Normal = BEGIN, ///< Normal/Standing
            RightHand,      ///< Right Hand Attack
            LeftHand,       ///< Left hand Attack
            Skill,          ///< use Skill
            Dead,           ///< Dead
            BadStatus,      ///< Bad BattlerStatus (Poison, Blind, ...)
            Defending,      ///< Defending
            MoveLeft,       ///< move Left
            MoveRight,      ///< move Right
            Win,            ///< Win/Victorious
            Item,           ///< use Item
            Damage,         ///< Damaged/Hit
            END)

/// Class Option
BETTER_ENUM(BattlerOption, size_t, BEGIN,
            LessDamage = BEGIN, ///< 1/4 damage less
            HigherGuard,        ///< 1/4 damage less by defending
            DoubleItemEffect,   ///< Double Effect of UseItem, recover HP/MP
            END)


/// Learn Skill
class LearnSkill {
    private:
    int lvl_ = 0;
    std::string skill_name_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("lvl", lvl_));
        ar(cereal::make_nvp("skill_name", skill_name_));
    }


    public:
    LearnSkill() = default;

    /**
     * @param lvl Level
     * @param skill Skill
     * @brief set required Level and learn Skill
     */
    LearnSkill(int lvl, const Skill& skill);

    /// learn Skill
    std::string getSkill() const { return this->skill_name_; }
    std::string getSkillName() const { return this->skill_name_; }

    /// required Level
    int getLvL() const { return this->lvl_; }

    void setLvL(int lvl) { this->lvl_ = lvl; }

    void setSkill(const Skill& skill) { this->skill_name_ = skill.getName(); }
};

/// DataBattler Class
class Battler {
    private:
    earr::enum_array<Attribute, int> attrbasis_;
    earr::enum_array<Attribute, int> attrinflation_;

    int startlvl_ = 0;
    int minlvl_ = 0;
    int maxlvl_ = 0;

    std::vector<LearnSkill> skills_;

    /// Resist of Element (key => Element Name, value = Resist)
    std::unordered_map<std::string, Resist> statusresist_;

    /// Resist of Element (key => Element Name, value = Resist)
    std::unordered_map<std::string, Resist> elementresist_;

    earr::enum_array<BattlerOption, bool> option_;

    std::string name_;

    int hitrate_ = 0;
    int criticalhitrate_ = 0;
    int evarate_ = 0;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("attrbasis", attrbasis_));
        ar(cereal::make_nvp("attrinflation", attrinflation_));

        ar(cereal::make_nvp("startlvl", startlvl_));
        ar(cereal::make_nvp("minlvl", minlvl_));
        ar(cereal::make_nvp("maxlvl", maxlvl_));

        ar(cereal::make_nvp("skills", skills_));

        ar(cereal::make_nvp("statusresist", statusresist_));
        ar(cereal::make_nvp("elementresist", elementresist_));

        ar(cereal::make_nvp("option", option_));
        ar(cereal::make_nvp("name", name_));

        ar(cereal::make_nvp("hitrate", hitrate_));
        ar(cereal::make_nvp("criticalhitrate", criticalhitrate_));
        ar(cereal::make_nvp("evarate", evarate_));
    }

    public:
    Battler();

    virtual ~Battler() = default;
    Battler(const Battler&) = default;
    Battler& operator=(const Battler&) = default;
    Battler(Battler&&) = default;
    Battler& operator=(Battler&&) = default;

    /// Basis value
    /// of all
    /// Attibutes
    const earr::enum_array<Attribute, int>& getAttrBasis() const {
        return this->attrbasis_;
    }

    /**
     * @param attr Attribute
     * @return Basis value of Attibute
     */
    int getAttrBasis(Attribute attr) const {
        return earr::enum_array_at(this->attrbasis_, attr);
    }

    /// Inflation value of all Attibutes
    const earr::enum_array<Attribute, int>& getAttrInflation() const {
        return this->attrinflation_;
    }

    /**
     * @param attr Attribute
     * @return Inflation value of Attibute
     */
    int getAttrInflation(Attribute attr) const {
        return earr::enum_array_at(this->attrinflation_, attr);
    }

    /// Start Level
    int getStartLvL() const { return this->startlvl_; }

    /// minimal Level
    int getMinLvL() const { return this->minlvl_; }

    /// maximal Level
    int getMaxLvL() const { return this->maxlvl_; }

    /// learn Skills
    const std::vector<LearnSkill>& getSkills() const { return this->skills_; }

    /**
     * @param name Skillname
     * @return learn Skill
     */
    decltype(auto) getSkill(std::string name) const {
        auto find_byName = [name](const LearnSkill& skill) {
            return skill.getSkillName() == name;
        };

        return std::find_if(std::begin(this->skills_), std::end(this->skills_),
                            find_byName);
    }

    /// BattlerStatus Resist
    const std::unordered_map<std::string, Resist>& getStatusResist() const {
        return this->statusresist_;
    }

    /**
     * @param battlerstatus_name BattlerStatus name
     * @return BattlerStatus Resist
     */
    Resist getStatusResist(std::string battlerstatus_name) const {
        auto it = this->statusresist_.find(battlerstatus_name);

        return (it != this->statusresist_.end()) ? it->second : +Resist::Normal;
    }

    /// Element Resist
    const std::unordered_map<std::string, Resist>& getElementResist() const {
        return this->elementresist_;
    }

    /**
     * @param element_name Element Name
     * @return Element Resist
     */
    Resist getElementResist(std::string element_name) const {
        auto it = this->elementresist_.find(element_name);

        return (it != this->elementresist_.end()) ? it->second
                                                  : +Resist::Normal;
    }

    /// Battler Options
    const earr::enum_array<BattlerOption, bool>& getOption() const {
        return this->option_;
    }

    /**
     * @param option BattlerOption
     * @return true, BattlerOption is ON
     */
    bool getOption(BattlerOption option) const {
        return earr::enum_array_at(this->option_, option);
    }

    /// Name
    std::string getName() const { return this->name_; }

    /// Basis Normal HitRate (without Equip, Boni, ...)
    int getHitRate() const { return this->hitrate_; }

    /// Basis Critical HitRate (without Equip, Boni, ...)
    int getCriticalHitRate() const { return this->criticalhitrate_; }

    /// Basis EvadeRate (without Equip, Boni, ...)
    int getEvaRate() const { return this->evarate_; }

    void setSkills(const std::vector<LearnSkill>& skills) {
        this->skills_ = skills;
    }

    void setAttrBasis(const earr::enum_array<Attribute, int>& attrbasis) {
        this->attrbasis_ = attrbasis;
    }

    /**
     * @param attr Attribute
     * @param value new Basis value
     * @brief set Basic value of Attribute
     */
    void setAttrBasis(Attribute attr, int value) {
        earr::enum_array_set(this->attrbasis_, attr, value);
    }

    void
    setAttrInflation(const earr::enum_array<Attribute, int>& attrinflation) {
        this->attrinflation_ = attrinflation;
    }

    /**
     * @param attr Attribute
     * @param value new Inflation value
     * @brief set Inflation value of Attribute
     */
    void setAttrInflation(Attribute attr, int value) {
        earr::enum_array_set(this->attrinflation_, attr, value);
    }

    void setStartLvL(int lvl) { this->startlvl_ = lvl; }

    void setMinLvL(int lvl) { this->minlvl_ = lvl; }

    void setMaxLvL(int lvl) { this->maxlvl_ = lvl; }

    void setStatusResist(const BattlerStatus& battlerstatus, Resist resist) {
        this->statusresist_[battlerstatus.getName()] = resist;
    }

    /// remove all Resist of BattlerStatus
    void clearStatusResist() { this->statusresist_.clear(); }

    /**
     * @param element Element
     * @param resist Resist of Element
     * @brief set Resist of Element
     */
    void setElementResist(const Element& element, Resist resist) {
        this->elementresist_[element.getName()] = resist;
    }

    /// remove all Resist of Element
    void clearElementResist() { this->elementresist_.clear(); }

    void setOption(const earr::enum_array<BattlerOption, bool>& option) {
        this->option_ = option;
    }

    /**
     * @param option Battler Option
     * @param active Option on/off
     * @brief set Battler Option
     */
    void setOption(BattlerOption option, bool active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setName(std::string name) { this->name_ = name; }

    void setHitRate(int hitrate) { this->hitrate_ = hitrate; }

    void setCriticalHitRate(int criticalhit) {
        this->criticalhitrate_ = criticalhit;
    }

    void setEvaRate(int evarate) { this->evarate_ = evarate; }
};
} // namespace data

#endif // DATA_BATTLER_H_
