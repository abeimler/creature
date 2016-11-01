#ifndef COMPONENT_GAME_CREATUREGENE_H_
#define COMPONENT_GAME_CREATUREGENE_H_

#include "Data/Creature.h"
#include "Data/Food.h"

#include "Component/Basic.h"

#include "Component/Game/CreatureBattler.h"
#include "Component/Game/CreatureBattlerGene.h"
#include "Component/Game/CreatureMemory.h"

#include "Component/DateTimer.h"
#include "Component/Game/ProgressTimer.h"

#include "Component/Game/CreatureProgressTimers.h"

namespace gamecomp {

struct CreatureGeneWaitTime {
    template <class T>
    using waittime_t = earr::enum_array<T, std::chrono::milliseconds>;

    /// Wartezeiten für den CreatureProgressTimer
    waittime_t<CreatureProgressTimer> timer;

    /// Wartezeiten für den CreatureProgressTimerCallback
    waittime_t<CreatureProgressTimerCallback> callback;

    /// Wartezeit für den CreatureProgressTimerIncrement
    waittime_t<CreatureProgressTimerIncrement> increment;

    /// Wartezeit für den CreatureProgressTimerCallback Starvation
    waittime_t<StarvationPhase> starvation;

    /// Wartezeit für den CreatureProgressTimerCallback ShortTermMemory
    waittime_t<CreatureActivity> shorttermmemory;

    /// Wartezeit für den CreatureProgressTimerCallback MediumTermMemory
    waittime_t<CreatureActivity> mediumtermmemory;
};


struct CreatureGeneTraining {
    /// maximaler overlay Hunger bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    double max_hungryoverlay_intraining = 0.0;

    /// maximaler overlay Durst bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    double max_thirstyoverlay_intraining = 0.0;

    /// maximale overlay Müdigkeit bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    double max_tiredoverlay_intraining = 0.0;

    /// mindest trainigszeit die erreicht werden muss um das mindest training
    /// abzuschliesen
    std::chrono::milliseconds min_trainitime;

    /// trainigszeit die erreicht werden muss um ein mittleres training
    /// abzuschliesen
    std::chrono::milliseconds middle_trainitime;

    /// trainigszeit die erreicht werden muss um ein gutes training
    /// abzuschliesen
    std::chrono::milliseconds good_trainitime;
};

struct CreatureGenePerEvolution {
    /// WarteZeit für ...
    CreatureGeneWaitTime waittime;

    /// Trainings Eigenschaften
    CreatureGeneTraining training;

    /// warte zeit wenn Creature weggelaufen ist
    std::chrono::milliseconds runawaytime_unluck;


    /// Statuswert der erreicht werden muss damit die
    /// Creature ein guten Schlaf hat
    double needsleepinpercent;

    /// Statuswert der erreicht werden muss damit die
    /// Creature ein guten Schlaf im Krankenhaus hat
    double needrestinhospitalinpercent;
};

/// GameCreature Genetik
struct CreatureGeneComponent {
    /// Creature Geschlecht
    data::CreatureGender gender = data::CreatureGender::None;

    /// Nummer der Generation
    size_t generationnr = 0;

    double min_bmi = 0.0;      ///< minimal BMI
    double ideal_bmi = 0.0;    ///< Ideal BMI
    double max_bmi = 0.0;      ///< maximal BMI
    double max_bodysize = 0.0; ///< maximale Körpergröße
    double bodymass = 0.0;     ///< Körpermasse
    double min_weight = 0.0;   ///< minimal Gewicht
    double max_weight = 0.0;   ///< maximal Gewicht

    /// benötigte Müdigkeit damit es Schlafen gehen will
    double cangosleep_at_tired = 0.0;

    /// maximale Haufen die es aufeinmal legen kann
    int max_digestionheap = 0;

    /// Mehr Eigenschaften pro CreatureLevel
    earr::enum_array<data::CreatureLevel, CreatureGenePerEvolution>
        perevolution;


    /// Maximale Lebensdauer (Lebenserwartung)
    std::chrono::milliseconds totalmaxlifetime;
};

} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREGENE_H_
