#ifndef DATA_SKILL_H_
#define DATA_SKILL_H_

#include "Data/BattlerStatus.h"
#include "Data/Element.h"

namespace data {

/// Skill Option
BETTER_ENUM(SkillOption, size_t, Absorb,
            BEGIN = Absorb,  ///< Absort
            IgnoreDefensive, ///< Ignore Defensive
            PhysicalAttack,  ///< Physical Attack
            CanUseinBattle,  ///< can use in Battle
            CanUseinField,   ///< can use in Field/Map

            /// only on dead Character
            /// (dont use OnlyOnDeadChara and OnDeadChara together)
            OnlyOnDeadChara,

            /// on dead Character and alive Character
            /// (dont use OnlyOnDeadChara and OnDeadChara together)
            OnDeadChara, END)

/// Skill
class Skill {
    private:
    std::string name_;

    std::string description_;
    earr::enum_array<SkillOption, bool> option_;

    attr_t mpcost_ = 0;
    bool inpercent_ = false;

    TargetOption target_ = TargetOption::OneEnemy;

    int atknumbers_ = 1;
    percent_rate_t hitrate_ = 100;

    attr_t basehpdamage_ = 0;
    attr_t basempdamage_ = 0;
    attr_t variance_ = 0;
    attr_t atk_ = 0;
    attr_t inte_ = 0;

    std::vector<std::string> addstatuses_;
    std::vector<std::string> removestatuses_;
    std::vector<std::string> elements_;


    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("name_", name_));

        ar(cereal::make_nvp("description", description_));
        ar(cereal::make_nvp("option", option_));
        ar(cereal::make_nvp("mpcost", mpcost_));
        ar(cereal::make_nvp("inpercent", inpercent_));

        ar(cereal::make_nvp("target", target_));

        ar(cereal::make_nvp("atknumbers", atknumbers_));
        ar(cereal::make_nvp("hitrate", hitrate_));
        ar(cereal::make_nvp("basehpdamage", basehpdamage_));
        ar(cereal::make_nvp("basempdamage", basempdamage_));
        ar(cereal::make_nvp("variance", variance_));
        ar(cereal::make_nvp("atk", atk_));
        ar(cereal::make_nvp("inte", inte_));

        ar(cereal::make_nvp("addstatuses", addstatuses_));
        ar(cereal::make_nvp("removestatuses", removestatuses_));
        ar(cereal::make_nvp("elements", elements_));
    }


    public:
    Skill();

    /// Skillname
    std::string getName() const { return this->name_; }

    /// Descrption
    std::string getDescription() const { return this->description_; }

    const earr::enum_array<SkillOption, bool>& getOption() const {
        return this->option_;
    }
    bool getOption(SkillOption option) const {
        return earr::enum_array_at(this->option_, option);
    }

    attr_t getMPCost() const { return this->mpcost_; }
    bool isMPCostInPercent() const { return this->inpercent_; }

    TargetOption getTarget() const { return this->target_; }

    int getAtkNumbers() const { return this->atknumbers_; }
    percent_rate_t getHitRate() const { return this->hitrate_; }

    attr_t getBaseHPDamage() const { return this->basehpdamage_; }
    attr_t getBaseMPDamage() const { return this->basempdamage_; }
    attr_t getVariance() const { return this->variance_; }
    attr_t getATK() const { return this->atk_; }
    attr_t getINT() const { return this->inte_; }

    const std::vector<std::string>& getAddStatuses() const {
        return this->addstatuses_;
    }

    const std::vector<std::string>& getRemoveStatuses() const {
        return this->removestatuses_;
    }

    const std::vector<std::string>& getElements() const {
        return this->elements_;
    }

    void setName(std::string name) { this->name_ = name; }

    void setDescription(std::string description) {
        this->description_ = description;
    }

    void setOption(const earr::enum_array<SkillOption, bool>& option) {
        this->option_ = option;
    }
    void setOption(SkillOption option, bool active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setMPCost(attr_t mpcost) { this->mpcost_ = mpcost; }

    void setIsMPCostInpercent(bool inpercent) { this->inpercent_ = inpercent; }

    void setTarget(TargetOption target) { this->target_ = target; }

    void setAtkNumbers(int atknumbers) { this->atknumbers_ = atknumbers; }
    void setHitRate(percent_rate_t hitrate) { this->hitrate_ = hitrate; }

    void setBaseHPDamage(attr_t basehpdamage) {
        this->basehpdamage_ = basehpdamage;
    }
    void setBaseMPDamage(attr_t basempdamage) {
        this->basempdamage_ = basempdamage;
    }
    void setVariance(attr_t variance) { this->variance_ = variance; }
    void setATK(attr_t atk) { this->atk_ = atk; }
    void setINT(attr_t inte) { this->inte_ = inte; }

    void addAddStatus(const BattlerStatus& battlerstatus) {
        this->addstatuses_.push_back(battlerstatus.getName());
    }
    void addRemoveStatus(const BattlerStatus& battlerstatus) {
        this->removestatuses_.push_back(battlerstatus.getName());
    }
    void addElement(const Element& element) {
        this->elements_.push_back(element.getName());
    }

    decltype(auto) getAddStatus(std::string name) const {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return name == battlerstatus_name;
        };

        return std::find_if(std::begin(this->addstatuses_),
                            std::end(this->addstatuses_), find_byName);
    }

    decltype(auto) getRemoveStatus(std::string name) const {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return name == battlerstatus_name;
        };

        return std::find_if(std::begin(this->removestatuses_),
                            std::end(this->removestatuses_), find_byName);
    }

    decltype(auto) getElement(std::string name) const {
        auto find_byName = [name](const std::string& element_name) {
            return name == element_name;
        };

        return std::find_if(std::begin(this->elements_),
                            std::end(this->elements_), find_byName);
    }
};
} // namespace data

#endif // DATA_SKILL_H_
