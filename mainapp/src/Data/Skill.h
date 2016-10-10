#ifndef DATA_SKILL_H_
#define DATA_SKILL_H_

#include "Data/BattlerStatus.h"
#include "Data/Element.h"

namespace data {

/// Skill Option
BETTER_ENUM(SkillOption, size_t, BEGIN,
            Absorb = BEGIN,  ///< Absort
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

    std::string descrption_;
    earr::enum_array<SkillOption, bool> option_;
    int mpcost_ = 0;
    bool inpercent_ = false;
    TargetOption target_ = TargetOption::OneEnemy;
    int atknumbers_ = 1;
    int hitrate_ = 100;
    int basehpdamage_ = 0;
    int basempdamage_ = 0;
    int variance_ = 0;
    int atk_ = 0;
    int inte_ = 0;

    std::vector<std::string> addstatuses_;
    std::vector<std::string> removestatuses_;
    std::vector<std::string> elements_;

    public:
    Skill();

    /// Skillname
    std::string getName() const { return this->name_; }

    /// Descrption
    std::string getDescrption() const { return this->descrption_; }

    const earr::enum_array<SkillOption, bool>& getOption() const {
        return this->option_;
    }
    bool getOption(SkillOption option) const {
        return earr::enum_array_at(this->option_, option);
    }

    int getMPCost() const { return this->mpcost_; }
    bool isMPCostInPercent() const { return this->inpercent_; }
    TargetOption getTarget() const { return this->target_; }
    int getAtkNumbers() const { return this->atknumbers_; }
    int getHitRate() const { return this->hitrate_; }
    int getBaseHPDamage() const { return this->basehpdamage_; }
    int getBaseMPDamage() const { return this->basempdamage_; }
    int getVariance() const { return this->variance_; }
    int getATK() const { return this->atk_; }
    int getINT() const { return this->inte_; }

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

    void setDescrption(std::string descrption) {
        this->descrption_ = descrption;
    }

    void setOption(const earr::enum_array<SkillOption, bool>& option) {
        this->option_ = option;
    }
    void setOption(SkillOption option, bool active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setMPCost(int mpcost) { this->mpcost_ = mpcost; }
    void setIsMPCostInpercent(bool inpercent) { this->inpercent_ = inpercent; }
    void setTarget(TargetOption target) { this->target_ = target; }
    void setAtkNumbers(int atknumbers) { this->atknumbers_ = atknumbers; }
    void setHitRate(int hitrate) { this->hitrate_ = hitrate; }
    void setBaseHPDamage(int basehpdamage) {
        this->basehpdamage_ = basehpdamage;
    }
    void setBaseMPDamage(int basempdamage) {
        this->basempdamage_ = basempdamage;
    }
    void setVariance(int variance) { this->variance_ = variance; }
    void setATK(int atk) { this->atk_ = atk; }
    void setINT(int inte) { this->inte_ = inte; }

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
