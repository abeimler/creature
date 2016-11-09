#ifndef ENTITY_GAME_CREATUREENTITYCREATOR_H_
#define ENTITY_GAME_CREATUREENTITYCREATOR_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Component/DateTimer.h"

#include "Component/Game/Battler.h"
#include "Component/Game/CreatureBattler.h"
#include "Component/Game/CreatureMemory.h"
#include "Component/Game/CreatureGene.h"
#include "Component/Game/Creature.h"

#include "Entity/Game/TimerUtil.h"
#include "Entity/Game/DateTimerUtil.h"
#include "Entity/Game/ProgressTimerUtil.h"

#include "Entity/EntityCreator.h"

#include "Entity/Game/CreatureBattlerCreator.h"

#include "Entity/Game/Entitys.h"


namespace gameentity {

class CreatureEntityCreator : public EntityCreator<Entity> {
    private:
    computil::TimerUtil timer_util_;
    computil::DateTimerUtil datetimer_util_;
    gamecomputil::ProgressTimerUtil progresstimer_util_;

    CreatureBattlerCreator creaturebattler_creator_;

    std::chrono::seconds min_needrefreshin_ = DEFAULT_MIN_NEEDREFRESHIN;
    std::chrono::seconds max_needrefreshin_ = DEFAULT_MAX_NEEDREFRESHIN;
    std::chrono::seconds min_totallifetime_ = DEFAULT_MIN_TOTALLIFETIME;
    std::chrono::seconds ageingtime_ = DEFAULT_AGEINGTIME;
    size_t max_short_memorysize_ = DEFAULT_MAX_SHORT_MEMORYSIZE;
    int max_short_memorysize_variance_ = DEFAULT_MAX_SHORT_MEMORYSIZE_VARIANCE;


    template <class E>
    void setCreatureGeneWaitTime(gamecomp::CreatureGeneWaitTime::waittime_t<E>& waittime,
        E index, std::chrono::milliseconds time) {
        earr::enum_array_set(waittime, index, time);
    }
    

    template <class E>
    void clearCreatureGeneWaitTime(gamecomp::CreatureGeneWaitTime::waittime_t<E>& waittime, E index) {
        earr::enum_array_set(waittime, index, std::chrono::milliseconds::zero());
    }


    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimer>
    createTimerWaitTime(data::CreatureLevel creature_level);

    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerCallback>
    createCallbackWaitTime(data::CreatureLevel creature_level);

    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureProgressTimerIncrement>
    createIncrementWaitTime(data::CreatureLevel creature_level);

    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::StarvationPhase>
    createStarvationWaitTime(data::CreatureLevel creature_level);

    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity>
    createShortTermMemoryWaitTime(data::CreatureLevel creature_level);

    gamecomp::CreatureGeneWaitTime::waittime_t<gamecomp::CreatureActivity>
    createMediumTermMemoryWaitTime(data::CreatureLevel creature_level);

    public:
    /**
     * @param s Körpergröße
     * @param g Gewicht
     * @param mg minimal Gewicht
     * @param ibmi ideal BMI
     * @param maxbmi maximal BMI
     * @return ermittle die Körpermasse
     */
    static double getBodyMass(double s, double g, double mg, double ibmi,
                             double minbmi, double maxbmi);

    static double getBodySize(double minbmi, double maxbmi, double bmi, double mass,
                             double minweight, double maxweight, double weight);

    static double getBMI(const gamecomp::CreatureGeneComponent& gene, double minweight,
                        double maxweight, double weight, double bodysize);

    static double getBMI(const data::Creature& creature,
                        const gamecomp::CreatureGeneComponent& gene, double weight);

    static double getBMI(const data::Creature& creature,
                        const gamecomp::CreatureGeneComponent& gene,
                        const gamecomp::CreatureBodyComponent& body);

    inline static double getBMI(const gamecomp::CreatureDataComponent& creature_data,
                        const gamecomp::CreatureGeneComponent& gene,
                        const gamecomp::CreatureBodyComponent& body) {
        return getBMI(creature_data.creature, gene, body);
    }


    /**
     * @param creature DataCreature
     * @param gene CreatureGene
     * @return ermittle die Körpermasse
     *        (durch BMI,Gewicht, Körpergroesse, ...)
     * @see getIdealMass(float s, float g, float mg, float ibmi,
     *                   float maxbmi)
     */
    static double getBodyMass(const data::Creature& creature,
                              const gamecomp::CreatureGeneComponent& gene);

    static double getBodyMass(const gamecomp::CreatureDataComponent& creature_data,
                              const gamecomp::CreatureGeneComponent& gene) {
        return getBodyMass(creature_data.creature, gene);
    }

    /**
     * @param gene CreatureGene
     * @param s Körpergröße
     * @param g Gewicht
     * @param mg minimal Gewicht
     * @return ermittle die Körpermasse
     *        (durch BMI,Gewicht, Körpergröse, ...)
     * @see getIdealMass(float s, float g, float mg, float ibmi,
     *                   float maxbmi)
     */
    static double getBodyMass(const gamecomp::CreatureGeneComponent& gene, 
                              double s, double g, double mg);


    static constexpr std::chrono::seconds DEFAULT_MIN_NEEDREFRESHIN =
        std::chrono::seconds(1);
    static constexpr std::chrono::seconds DEFAULT_MAX_NEEDREFRESHIN =
        std::chrono::hours(24) * 7;
    static constexpr std::chrono::seconds DEFAULT_MIN_TOTALLIFETIME =
        std::chrono::hours(24) * 365 * 3;
    static constexpr std::chrono::seconds DEFAULT_AGEINGTIME =
        DEFAULT_MIN_TOTALLIFETIME / 100;

    static constexpr size_t DEFAULT_MAX_SHORT_MEMORYSIZE = 7;
    static constexpr int DEFAULT_MAX_SHORT_MEMORYSIZE_VARIANCE = 2;

    static constexpr int CANGOSLEEP_AT_TIRED = 88;
    static constexpr int MAX_DIGESTIONHEAP = 3;

    static constexpr double MIN_BMI = 18;
    static constexpr double IDEAL_BMI = 26;
    static constexpr double MAX_BMI = 50;

    static constexpr double LOW_MIN_BMI = 14;
    static constexpr double LOW_IDEAL_BMI = 22;
    static constexpr double LOW_MAX_BMI = 40;

    static constexpr double HIGH_MIN_BMI = 20;
    static constexpr double HIGH_IDEAL_BMI = 33;
    static constexpr double HIGH_MAX_BMI = 50;


    static_assert(DEFAULT_AGEINGTIME > std::chrono::seconds::zero(),
                  "DEFAULT_AGEINGTIME can not be zero");

    static_assert(DEFAULT_MIN_NEEDREFRESHIN <= DEFAULT_MAX_NEEDREFRESHIN,
                  "DEFAULT_MIN_NEEDREFRESHIN must be smaller then "
                  "DEFAULT_MAX_NEEDREFRESHIN");

    static_assert(MIN_BMI <= MAX_BMI, "MIN_BMI must be smaller then MAX_BMI");
    static_assert(IDEAL_BMI >= MIN_BMI && IDEAL_BMI <= MAX_BMI,
                  "IDEAL_BMI must be between MIN_BMI - MAX_BMI");



    template<class E>
    static std::chrono::milliseconds& getCreatureProgressTimersWaitTime(earr::enum_array<E, gamecomp::ProgressTimer>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).waittime, creature_level);
    }

    template<class E>
    static std::chrono::milliseconds& getCreatureProgressTimersWaitTime(earr::enum_array<E, gamecomp::ProgressTimerCallback>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).base.waittime, creature_level);
    }

    template<class E>
    static std::chrono::milliseconds& getCreatureProgressTimersWaitTime(earr::enum_array<E, gamecomp::ProgressTimerIncrement>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).base.waittime, creature_level);
    }


    template<class E>
    static const std::chrono::milliseconds& getCreatureProgressTimersWaitTime(const earr::enum_array<E, gamecomp::ProgressTimer>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).waittime, creature_level);
    }

    template<class E>
    static const std::chrono::milliseconds& getCreatureProgressTimersWaitTime(const earr::enum_array<E, gamecomp::ProgressTimerCallback>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).base.waittime, creature_level);
    }

    template<class E>
    static const std::chrono::milliseconds& getCreatureProgressTimersWaitTime(const earr::enum_array<E, gamecomp::ProgressTimerIncrement>& timer, E index, data::CreatureLevel creature_level){
        return earr::enum_array_at(earr::enum_array_at(timer, index).base.waittime, creature_level);
    }

    CreatureEntityCreator() = default;

    std::chrono::seconds getMinNeedRefreshIn() const {
        return this->min_needrefreshin_;
    }
    std::chrono::seconds getMaxNeedRefreshIn() const {
        return this->max_needrefreshin_;
    }
    std::chrono::seconds getMinTotalLifetime() const {
        return this->min_totallifetime_;
    }
    std::chrono::seconds getAgeingTime() const { return this->ageingtime_; }

    size_t getMaxShortMemorySize() const { return this->max_short_memorysize_; }
    int getMaxShortMemorySizeVariance() const {
        return this->max_short_memorysize_variance_;
    }


    void create(Entity& entity) override;

    void create(Entity& entity,
                const data::Creature& creature,
                std::chrono::system_clock::time_point realtime,
                double realtime_factor);
    inline void create(Entity& entity,
                       const data::Creature& creature,
                       std::chrono::system_clock::time_point realtime) {
        create(entity, creature, realtime, 1.0);
    }
    inline void create(Entity& entity,
                       const data::Creature& creature) {
        auto realtime = std::chrono::system_clock::now();
        create(entity, creature, realtime);
    }



    gamecomp::CreatureProgressTimersComponent
    createCreatureProgressTimers(std::chrono::system_clock::time_point time,
                                 double realtime_factor);
    inline gamecomp::CreatureProgressTimersComponent
    createCreatureProgressTimers(std::chrono::system_clock::time_point time) {
        return createCreatureProgressTimers(time, 1.0);
    }
    inline gamecomp::CreatureProgressTimersComponent createCreatureProgressTimers() {
        auto realtime = std::chrono::system_clock::now();
        return createCreatureProgressTimers(realtime);
    }


    gamecomp::CreatureProgressTimersComponent createCreatureProgressTimersCreature(
        std::chrono::system_clock::time_point time, double realtime_factor);

    void setCreatureProgressTimersRealTime(
        gamecomp::CreatureProgressTimersComponent& timer,
        std::chrono::system_clock::time_point time, double realtime_factor);

    void setCreatureProgressTimersRealTimeFromLifetimer(
        gamecomp::CreatureProgressTimersComponent& timer);

    void
    setupCreatureProgressTimers(gamecomp::CreatureProgressTimersComponent& timers,
                                const data::Creature& creature,
                                const gamecomp::CreatureLifeComponent& life,
                                const gamecomp::CreatureGeneComponent& gene,
                                const gamecomp::CreatureBodyComponent& body);

    inline void
    setupCreatureProgressTimers(gamecomp::CreatureProgressTimersComponent& timers,
                                const gamecomp::CreatureDataComponent& creature_data,
                                const gamecomp::CreatureLifeComponent& life,
                                const gamecomp::CreatureGeneComponent& gene,
                                const gamecomp::CreatureBodyComponent& body) {
        setupCreatureProgressTimers(timers, creature_data.creature, life, gene, body); 
    }


    gamecomp::CreatureGeneComponent
    createCreatureGene(const data::Creature& creature);

    inline gamecomp::CreatureGeneComponent
    createCreatureGene(const gamecomp::CreatureDataComponent& creature_data) {
        return createCreatureGene(creature_data.creature);
    }

    gamecomp::CreatureMemoryComponent createCreatureMemory();
    gamecomp::CreatureTrainingComponent createCreatureTraining();

    gamecomp::CreatureBodyComponent
    createCreatureBody(const data::Creature& creature,
                       const gamecomp::CreatureGeneComponent& gene);
    
    inline gamecomp::CreatureBodyComponent
    createCreatureBody(const gamecomp::CreatureDataComponent& creature_data,
                       const gamecomp::CreatureGeneComponent& gene) {
        return createCreatureBody(creature_data.creature, gene);
    }


    gamecomp::CreaturePsycheComponent createCreaturePsyche();

    gamecomp::CreatureLifeComponent
    createCreatureLife(const data::Creature& creature,
                       std::chrono::system_clock::time_point realtime,
                       const gamecomp::CreatureBattlerComponent& battler,
                       const gamecomp::CreatureGeneComponent& gene);

    inline gamecomp::CreatureLifeComponent
    createCreatureLife(const gamecomp::CreatureDataComponent& creature_data,
                       std::chrono::system_clock::time_point realtime,
                       const gamecomp::CreatureBattlerComponent& battler,
                       const gamecomp::CreatureGeneComponent& gene) {
        return createCreatureLife(creature_data.creature, realtime, battler, gene);
    }
};
} // namespace gameentity


#endif // ENTITY_GAME_CREATUREENTITYCREATOR_H_
