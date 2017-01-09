#ifndef DATA_USEITEM_H_
#define DATA_USEITEM_H_

#include "Data/Basic.h"

#include "Data/BattlerStatus.h"
#include "Data/Creature.h"
#include "Data/Item.h"

namespace data {

/// UseItem Option
BETTER_ENUM(UseItemOption, size_t, CanUseinBattle,
            BEGIN = CanUseinBattle, ///< can use in Battle
            CanUseinField,          ///< can use in Field/Map

            /// only on Dead Character
            /// (dont use OnlyOnDeadChara and OnDeadChara together)
            OnlyOnDeadChara,

            /// on Dead Character, too
            /// (dont use OnlyonDeadChara and OnDeadChara together)
            OnDeadChara,
            AllCanUseIt, ///< can use it all
            END)

/// UseItem Item
class UseItem : public Item {
    private:
    item_use_t canuse_ = CAN_USE_ITEM_ONCE;
    TargetOption target_ = TargetOption::OneEnemy;

    atknumbers_t atknumbers_ = 1;
    earr::enum_array<UseItemOption, bool> option_;

    earr::enum_array<Attribute, attr_t> attr_;

    attr_t rehp_ = 0;
    option_t rehp_inpercent_ = false;

    attr_t remp_ = 0;
    option_t remp_inpercent_ = false;

    std::vector<std::string> creatures_;
    std::vector<std::string> addstatuses_;
    std::vector<std::string> removestatuses_;

    /// @todo make it optional
    std::string learnskill_;

    /// @todo make it optional
    std::string useskill_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("_base", cereal::base_class<Item>(this)));

        ar(cereal::make_nvp("canuse", canuse_));
        ar(cereal::make_nvp("target", target_));
        ar(cereal::make_nvp("atknumbers", atknumbers_));
        ar(cereal::make_nvp("option", option_));
        ar(cereal::make_nvp("attr", attr_));

        ar(cereal::make_nvp("rehp", rehp_));
        ar(cereal::make_nvp("rehp_inpercent", rehp_inpercent_));

        ar(cereal::make_nvp("remp", remp_));
        ar(cereal::make_nvp("remp_inpercent", remp_inpercent_));

        ar(cereal::make_nvp("creatures", creatures_));
        ar(cereal::make_nvp("addstatuses", addstatuses_));
        ar(cereal::make_nvp("removestatuses", removestatuses_));

        ar(cereal::make_nvp("learnskill", learnskill_));
        ar(cereal::make_nvp("useskill", useskill_));
    }

    protected:
    explicit UseItem(Item  item);

    public:
    /// constant for "can't use" @see UseItem.canuse_
    static constexpr item_use_t CANT_USE_ITEM = 0;

    /// constant for "can use unlimited" @see UseItem.canuse_
    static constexpr item_use_t CAN_USE_UNLIMITED = -1;

    /// constant for "can use once" @see UseItem.canuse_
    static constexpr item_use_t CAN_USE_ITEM_ONCE = 1;

    UseItem();

    virtual ~UseItem() = default;
    UseItem(const UseItem&) = default;
    UseItem& operator=(const UseItem&) = default;
    UseItem(UseItem&&) = default;
    UseItem& operator=(UseItem&&) = default;

    /// numbers of uses (unlimeted = -1, can't use = 0)
    item_use_t getCanUse() const { return this->canuse_; }

    /// target option
    TargetOption getTarget() const { return this->target_; }

    /// numbers of attack/uses at one use
    atknumbers_t getAtkNumbers() const { return this->atknumbers_; }

    /// UseItem Options
    const earr::enum_array<UseItemOption, bool>& getOption() const {
        return this->option_;
    }

    /**
     * @param option UseItem option
     * @return useItem option
     */
    option_t getOption(UseItemOption option) const {
        return earr::enum_array_at(this->option_, option);
    }

    /// Boni Attributes
    const earr::enum_array<Attribute, attr_t>& getAttr() const {
        return this->attr_;
    }

    /**
     * @param attr Attribute
     * @return Boni Attribute
     */
    attr_t getAttr(Attribute attr) const {
        return earr::enum_array_at(this->attr_, attr);
    }

    attr_t getReHP() const { return this->rehp_; }
    option_t isReHPinPercent() const { return this->rehp_inpercent_; }
    attr_t getReMP() const { return this->remp_; }
    option_t isReMPinPercent() const { return this->remp_inpercent_; }

    const std::vector<std::string>& getAddStatuses() const {
        return this->addstatuses_;
    }

    const std::vector<std::string>& getRemoveStatuses() const {
        return this->removestatuses_;
    }

    ts::bool_t canUseCreature(const Creature& creature) const {
        if (this->getOption(UseItemOption::AllCanUseIt)) {
            return true;
        }

        std::string creature_name = creature.getName();
        auto find_byName = [creature_name](const std::string& name) {
            return name == creature_name;
        };

        auto it = std::find_if(std::begin(this->creatures_),
                               std::end(this->creatures_), find_byName);

        return it != std::end(this->creatures_);
    }

    decltype(auto) getAddStatus(std::string name) {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return battlerstatus_name == name;
        };

        return std::find_if(std::begin(this->addstatuses_),
                            std::end(this->addstatuses_), find_byName);
    }

    bool isAddStatusFind(std::string name) {
        return getAddStatus(name) != std::end(this->addstatuses_);
    }

    decltype(auto) getRemoveStatus(std::string name) const {
        auto find_byName = [name](const std::string& battlerstatus_name) {
            return battlerstatus_name == name;
        };

        return std::find_if(this->removestatuses_.begin(),
                            this->removestatuses_.end(), find_byName);
    }

    ts::bool_t isRemoveStatusFind(std::string name) {
        return getRemoveStatus(name) != std::end(this->removestatuses_);
    }

    std::string getLearnSkillName() const { return this->learnskill_; }

    std::string getUseSkillName() const { return this->useskill_; }

    void setCanUse(item_use_t canuse) { this->canuse_ = canuse; }
    void setTarget(TargetOption target) { this->target_ = target; }
    void setAtkNumbers(atknumbers_t atknumbers) { this->atknumbers_ = atknumbers; }

    void setOption(const earr::enum_array<UseItemOption, option_t>& option) {
        this->option_ = option;
    }
    void setOption(UseItemOption option, option_t active) {
        earr::enum_array_set(this->option_, option, active);
    }

    void setAttr(const earr::enum_array<Attribute, attr_t>& attr) {
        this->attr_ = attr;
    }
    void setAttr(Attribute attr, attr_t value) {
        earr::enum_array_set(this->attr_, attr, value);
    }

    void setReHP(attr_t value) { this->rehp_ = value; }
    void setIsReHPinPercent(option_t ispercent) {
        this->rehp_inpercent_ = ispercent;
    }
    void setReHPinPercent(attr_t value) {
        this->rehp_ = value;
        this->rehp_inpercent_ = true;
    }
    void setReMP(attr_t value) { this->remp_ = value; }
    void setIsReMPinPercent(option_t ispercent) {
        this->remp_inpercent_ = ispercent;
    }
    void setReMPinPercent(attr_t value) {
        this->remp_ = value;
        this->remp_inpercent_ = true;
    }

    void addCreature(const Creature& creature) {
        this->creatures_.push_back(creature.getName());
    }

    void addAddStatus(const BattlerStatus& status) {
        this->addstatuses_.push_back(status.getName());
    }

    void addRemoveStatus(const BattlerStatus& status) {
        this->removestatuses_.push_back(status.getName());
    }

    void setLearnSkill(const Skill& skill) {
        this->learnskill_ = skill.getName();
    }

    void setUseSkill(const Skill& skill) { this->useskill_ = skill.getName(); }
};

} // namespace data

#endif // DATA_USEITEM_H_
