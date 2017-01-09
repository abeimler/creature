#ifndef DATA_CREATURE_H_
#define DATA_CREATURE_H_

#include "Data/Battler.h"
#include "Data/CreatureType.h"
#include "Data/Element.h"

namespace data {

/// Creature Normal-Animation Frames
BETTER_ENUM(CreatureAnimation, ts::unsigned_t,
            /// start at 12, see AnimationPose
            Standing = +AnimationPose::END,
            BEGIN = Standing, ///< Standing
            WalkingLeft,      ///< Walking left
            WalkingRight,     ///< Walking right
            Sitting,          ///< Sitting
            Eat,              ///< Eat
            Poop,             ///< Poop
            Refuse,           ///< Refuse
            LookAt,           ///< LookAt
            END)

/// Creature Misc-Animation Frames
BETTER_ENUM(CreatureAnimationMisc, ts::unsigned_t,
            /// start at 20, see CreatureAnimation
            Born = +CreatureAnimation::END,
            BEGIN = Born,  ///< Is Born
            Happy = BEGIN, ///< Happy
            EvolutionFrom, ///< evolution from ...
            EvolutionTo,   ///< ... evolution to
            END)


/// Creature Status-Animation Frames
BETTER_ENUM(CreatureStatusAnimation, ts::unsigned_t,
            /// start at 23, see CreatureAnimationMisc
            Normal = +CreatureAnimationMisc::END,
            BEGIN = Normal,
            Dead,     ///< Dead
            RunAway,  ///< Run Away
            Sleep,    ///< Sleep, Rest
            Hurt,     ///< Hurt, Ill
            Training, ///< In Training
            END)



/// GameCreature Status
BETTER_ENUM(CreatureStatus, ts::unsigned_t, Normal,
            BEGIN = Normal, ///< Normal Status (no Statuses)
            Dead,           ///< Dead
            RunAway,        ///< Run Away
            Sleep,          ///< Sleep
            InHospital,     ///< In Hospital
            RestInHospital, ///< Rest in Hospital
            Rest,           ///< Rest
            Hurt,           ///< Hurt
            Ill,            ///< Ill
            Training,       ///< In Training
            Unhappy,        ///< Unhappy
            Happy,          ///< Happy
            Hungry,         ///< Hungry
            Thirsty,        ///< Thirsty
            Replete,        ///< Replete
            Tired,          ///< Tired
            END)

/// Creature Level
BETTER_ENUM(CreatureLevel, ts::unsigned_t, Egg,
            BEGIN = Egg, ///< Egg
            Baby,        ///< Baby
            Baby2,       ///< Baby2
            Child,       ///< Child
            Adult,       ///< Adult
            Perfect,     ///< Perfect
            Ultimate,    ///< Ultimate
            END)

/// Creature Circadian Rhythm
BETTER_ENUM(
    CreatureCircadianRhythm, ts::unsigned_t, None,
    BEGIN = None, ///< None
    Crepuscular,  ///< Crepuscular      during twilight (i.e., dawn and dusk).
    Diurnal,      ///< Diurnal          during the day and sleeping, or other
                  ///                   inactivity, at night.
    Nocturnal,    ///< Nocturnal        activity during the night and sleeping
                  ///                   during the day.
    Variable,     ///< Variable
    Unknown,      ///< Unknown
    END)

/// Creature TrainingTime/ActiveTime
BETTER_ENUM(CreatureTrainTime, ts::unsigned_t, Morning,
            BEGIN = Morning, ///< Morning:      4 - 11 o'clock
            Noon,            ///< Noon:         12 - 16 o'clock
            AfterNoon,       ///< AfterNoon:    17 - 19 o'clock
            Evening,         ///< Evening:      20 - 22 o'clock
            Night,           ///< Night:        23 - 3 o'clock
            END)

/// Creature Gender
BETTER_ENUM(CreatureGender, size_t, None,
            BEGIN = None,  ///< None/Genderless
            Male,          ///< Male
            Female,        ///< Fermale
            Hermaphrodite, ///< Hermaphrodite
            END)



/// Condition to Evolution
class EvolutionCondition {
    private:
    weight_t weight_ = 0.0;
    luck_t luck_ = 0.0;
    disc_t disc_ = 0.0;
    option_t wasnotill_ = false;
    option_t wasnothurt_ = false;

    lvl_t mustevolveatlevel_ = MUSTEVOLVEATLEVEL_NONE;

    earr::enum_array<Attribute, attr_t> attr_;

    earr::enum_array<CreatureTrainTime, option_t> traintime_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("weight", weight_));
        ar(cereal::make_nvp("luck", luck_));
        ar(cereal::make_nvp("disc", disc_));

        ar(cereal::make_nvp("wasnotill", wasnotill_));
        ar(cereal::make_nvp("wasnothurt", wasnothurt_));

        ar(cereal::make_nvp("mustevolveatlevel", mustevolveatlevel_));
        ar(cereal::make_nvp("attr", attr_));

        ar(cereal::make_nvp("traintime", traintime_));
    }


    public:
    static constexpr lvl_t MUSTEVOLVEATLEVEL_NONE = -1;

    EvolutionCondition();

    /// set TrainingTime all true
    void setTrainTimeEveryDay();

    /// minimal weight
    weight_t getWeight() const { return this->weight_; }

    /// minimal luck
    luck_t getLuck() const { return this->luck_; }

    /// minimal discipline
    disc_t getDisc() const { return this->disc_; }

    /// true when was not ill
    option_t wasNotIll() const { return this->wasnotill_; }

    /// true when was not hurt
    option_t wasNotHurt() const { return this->wasnothurt_; }

    /// must evolve at Level (-1 = ignore)
    lvl_t getMustEvolveAtLevel() const { return this->mustevolveatlevel_; }

    /// minimal Attributes
    const earr::enum_array<Attribute, attr_t>& getAttr() const {
        return this->attr_;
    }

    /// Creature TrainingTimes/ActiveTimes
    const earr::enum_array<CreatureTrainTime, option_t>& getTrainTime() const {
        return this->traintime_;
    }

    /**
     * @param attr Attribute
     * @return minimal Attribute
     */
    attr_t getAttr(Attribute attr) const {
        return earr::enum_array_at(this->attr_, attr);
    }

    /**
     * @param traintime TrainingTime
     * @return true, Creature TrainingTime/ActiveTime
     */
    bool getTrainTime(CreatureTrainTime traintime) const {
        return earr::enum_array_at(this->traintime_, traintime);
    }

    void setWeight(weight_t weight) { this->weight_ = weight; }

    void setLuck(luck_t luck) { this->luck_ = luck; }

    void setDisc(disc_t disc) { this->disc_ = disc; }

    void setWasNotIll(option_t wasnotill) { this->wasnotill_ = wasnotill; }

    void setWasNotHurt(option_t wasnothurt) { this->wasnothurt_ = wasnothurt; }

    void setMustEvolveAtLevel(lvl_t level) { this->mustevolveatlevel_ = level; }

    void setAttr(const earr::enum_array<Attribute, attr_t>& attr) {
        this->attr_ = attr;
    }

    /**
     * @param attr Attribute
     * @param value Attribute value
     * @brief set minimal Attributes
     */
    void setAttr(Attribute attr, attr_t value) {
        earr::enum_array_set(this->attr_, attr, value);
    }

    void
    setTrainTime(const earr::enum_array<CreatureTrainTime, option_t>& traintime) {
        this->traintime_ = traintime;
    }

    /**
     * @param traintime Creature TrainingTime/ActiveTime
     * @param value TrainingTime condition on/off
     * @brief set Creature TrainingTime/ActiveTime option
     */
    void setTrainTime(CreatureTrainTime traintime, option_t value) {
        earr::enum_array_set(this->traintime_, traintime, value);
    }
};

/// Creature Data
class Creature : public Battler {
    private:
    CreatureLevel creaturelevel_ = CreatureLevel::Egg;

    std::vector<std::string> elements_;

    CreatureCircadianRhythm creaturerhythm_ = CreatureCircadianRhythm::None;

    std::string creaturetype_;

    weight_t minweight_ = 0.1;
    weight_t maxweight_ = 0.1;
    bodysize_t minbodysize_ = 0.1;
    bodysize_t maxbodysize_ = 0.1;

    std::vector<std::string> nextcreatures_;
    std::vector<std::string> prevcreatures_;
    std::vector<std::string> misscreatures_;

    EvolutionCondition evolcondition_;

    earr::enum_array<CreatureGender, distribution_factor_t> genderdistribution_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("_base", cereal::base_class<Battler>(this)));

        ar(cereal::make_nvp("creaturelevel", creaturelevel_));
        ar(cereal::make_nvp("elements", elements_));
        ar(cereal::make_nvp("creaturerhythm", creaturerhythm_));

        ar(cereal::make_nvp("creaturetype", creaturetype_));

        ar(cereal::make_nvp("minweight", minweight_));
        ar(cereal::make_nvp("maxweight", maxweight_));
        ar(cereal::make_nvp("minbodysize", minbodysize_));
        ar(cereal::make_nvp("maxbodysize", maxbodysize_));

        ar(cereal::make_nvp("nextcreatures", nextcreatures_));
        ar(cereal::make_nvp("prevcreatures", prevcreatures_));
        ar(cereal::make_nvp("misscreatures", misscreatures_));

        ar(cereal::make_nvp("evolcondition", evolcondition_));
        ar(cereal::make_nvp("genderdistribution", genderdistribution_));
    }

    public:
    Creature();

    explicit Creature(Battler battler);

    /// Creature Level
    CreatureLevel getCreatureLevel() const { return this->creaturelevel_; }

    /// Creature Circadian Rhythm
    CreatureCircadianRhythm getCreatureCircadianRhythm() const {
        return this->creaturerhythm_;
    }

    /// Elements
    const std::vector<std::string>& getElements() const {
        return this->elements_;
    }



    /**
     * @param name Elementname
     * @return have Element
     * @return element.end(), have not this Element
     */
    decltype(auto) getElement(std::string name) const {
        auto find_byName = [name](const std::string& element_name) {
            return name == element_name;
        };

        return std::find_if(std::begin(this->elements_),
                            std::end(this->elements_), find_byName);
    }

    /// Creature Type
    std::string getCreatureType() const { return this->creaturetype_; }

    /// minimal weight
    weight_t getMinWeight() const { return this->minweight_; }

    /// maximal weight
    weight_t getMaxWeight() const { return this->maxweight_; }

    /// minimal bodysize
    bodysize_t getBodySize() const { return this->minbodysize_; }

    /// minimal bodysize
    bodysize_t getMinBodySize() const { return this->minbodysize_; }

    /// maximal bodysize
    bodysize_t getMaxBodySize() const { return this->maxbodysize_; }

    /// next Creature Evolution
    const std::vector<std::string>& getNextCreatures() const {
        return this->nextcreatures_;
    }

    /// prev Creature Evolution
    const std::vector<std::string>& getPrevCreatures() const {
        return this->prevcreatures_;
    }

    /// miss/bad Creature Evolution
    const std::vector<std::string>& getMissCreatures() const {
        return this->misscreatures_;
    }

    /// Evolution condition for this Creature
    const EvolutionCondition& getEvolCondition() const {
        return this->evolcondition_;
    }

    /// Creature Gender distribution in %
    const earr::enum_array<CreatureGender, distribution_factor_t>&
    getGenderDistribution() const {
        return this->genderdistribution_;
    }

    /**
     * @param gender Creature Gender
     * @return Creature Gender distribution in %
     */
    distribution_factor_t getGenderDistribution(CreatureGender gender) const {
        return earr::enum_array_at(this->genderdistribution_, gender);
    }

    /**
     * @param p_creature_level Creature Level
     * @brief set Creature Level
     */
    void setCreatureLevel(CreatureLevel p_creature_level) {
        this->creaturelevel_ = p_creature_level;
    }

    /**
     * @param creaturerhythm Creature Circadian Rhythm
     * @brief set Creature Circadian Rhythm
     */
    void setCreatureCircadianRhythm(CreatureCircadianRhythm creaturerhythm) {
        this->creaturerhythm_ = creaturerhythm;
    }

    /**
     * @param elements Elements
     * @brief set Elements
     */
    void addElement(const Element& element) {
        this->elements_.push_back(element.getName());
    }

    /**
     * @param creaturetype Creature Type
     * @brief set Creature Type
     */
    void setCreatureType(const CreatureType& creaturetype) {
        this->creaturetype_ = creaturetype.getName();
    }

    /**
     * @param gender Creature Gender
     * @param value Creature Gender distribution in %
     * @brief set Creature Gender distribution
     */
    void setGenderDistribution(CreatureGender gender, distribution_factor_t value) {
        earr::enum_array_set(this->genderdistribution_, gender, value);
    }



    /**
     * @param nextcreatures next Creature Evolution
     * @brief set next Creature Evolution
     */
    void addNextCreature(const Creature& nextcreature) {
        this->nextcreatures_.push_back(nextcreature.getName());
    }

    /**
     * @param prescreatures prev Creature Evolution
     * @brief set prev Creature Evolution
     */
    void addPrevCreature(const Creature& prevcreature) {
        this->prevcreatures_.push_back(prevcreature.getName());
    }

    /**
     * @param misscreatures miss/bad Creature Evolution
     * @brief set miss Creature Evolution
     */
    void addMissCreature(const Creature& misscreature) {
        this->misscreatures_.push_back(misscreature.getName());
    }

    /**
     * @param evolcondition Evolution Condition
     * @brief set Evolution Condition
     */
    void setEvolCondition(const EvolutionCondition& evolcondition) {
        this->evolcondition_ = evolcondition;
    }

    /// remove all Elements
    void clearElements() { this->elements_.clear(); }

    /**
     * @param weight minimal weight
     * @brief set minimal weight
     */
    void setMinWeight(weight_t weight) { this->minweight_ = weight; }

    /**
     * @param weight maximal weight
     * @brief set maximal weight
     */
    void setMaxWeight(weight_t weight) { this->maxweight_ = weight; }

    /**
     * @param bodysize bodysize
     * @brief set minimal and maximal bodysize
     */
    void setBodySize(bodysize_t bodysize) {
        this->setBodySizeMin(bodysize);
        this->setBodySizeMax(bodysize);
    }

    /**
     * @param bodysize minimal bodysize
     * @brief set minimal bodysize
     */
    void setBodySizeMin(bodysize_t bodysize) { this->minbodysize_ = bodysize; }

    /**
     * @param bodysize maximal bodysize
     * @brief set maximal bodysize
     */
    void setBodySizeMax(bodysize_t bodysize) { this->maxbodysize_ = bodysize; }
};



/// Starter Creature
class CreatureStarter {
    private:
    std::string creature_name_;

    public:
    template <class Archive>
    void serialize(Archive& ar) {
        ar(cereal::make_nvp("creature_name", creature_name_));
    }

    public:
    CreatureStarter() = default;

    explicit CreatureStarter(const Creature& creature);

    /// Creature
    std::string getCreatureName() const { return this->creature_name_; }

    void setCreature(const Creature& creature) {
        this->creature_name_ = creature.getName();
    }
};

} // namespace data

#endif // DATA_CREATURE_H_
