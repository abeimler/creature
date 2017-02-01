#ifndef COMPONENT_GAME_CREATUREGENE_H_
#define COMPONENT_GAME_CREATUREGENE_H_

#include "Data/Creature.h"
#include "Data/Food.h"


#include "Component/Game/Basic.h"
#include "Component/Game/CreatureBattler.h"
#include "Component/Game/CreatureBattlerGene.h"
#include "Component/Game/CreatureMemory.h"

#include "Component/DateTimer.h"
#include "Component/Game/ProgressTimer.h"

#include "Component/Game/CreatureProgressTimers.h"

namespace gamecomp {

struct CreatureGeneWaitTime {

    /// Wartezeiten für den CreatureProgressTimer
    gene_waittime_t<CreatureProgressTimer> timer;

    /// Wartezeiten für den CreatureProgressTimerCallback
    gene_waittime_t<CreatureProgressTimerCallback> callback;

    /// Wartezeit für den CreatureProgressTimerIncrement
    gene_waittime_t<CreatureProgressTimerIncrement> increment;

    /// Wartezeit für den CreatureProgressTimerCallback Starvation
    gene_waittime_t<StarvationPhase> starvation;

    /// Wartezeit für den CreatureProgressTimerCallback ShortTermMemory
    gene_waittime_t<CreatureActivity> shorttermmemory;

    /// Wartezeit für den CreatureProgressTimerCallback MediumTermMemory
    gene_waittime_t<CreatureActivity> mediumtermmemory;
};


struct CreatureGeneTraining {
    /// maximaler overlay Hunger bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    progresstimer_percent_t max_hungryoverlay_intraining = 0.0;

    /// maximaler overlay Durst bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    progresstimer_percent_t max_thirstyoverlay_intraining = 0.0;

    /// maximale overlay Müdigkeit bei Training (wenn
    /// erreicht, wird das Training abgebrochen)
    progresstimer_percent_t max_tiredoverlay_intraining = 0.0;

    /// mindest trainigszeit die erreicht werden muss um das mindest training
    /// abzuschliesen
    traintime_t min_trainitime;

    /// trainigszeit die erreicht werden muss um ein mittleres training
    /// abzuschliesen
    traintime_t middle_trainitime;

    /// trainigszeit die erreicht werden muss um ein gutes training
    /// abzuschliesen
    traintime_t good_trainitime;


    progresstimer_percent_t cantrain_with_max_hungry = 0.0;
    progresstimer_percent_t cantrain_with_max_thirsty = 0.0;
    progresstimer_percent_t cantrain_with_max_tired = 0.0;
};

struct CreatureGenePerEvolution {
    /// WarteZeit für ...
    CreatureGeneWaitTime waittime;

    /// Trainings Eigenschaften
    CreatureGeneTraining training;

    /// warte zeit wenn Creature weggelaufen ist
    lifetime_t runawaytime_unluck;


    /// Statuswert der erreicht werden muss damit die
    /// Creature ein guten Schlaf hat
    progresstimer_percent_t needsleepinpercent;

    /// Statuswert der erreicht werden muss damit die
    /// Creature ein guten Schlaf im Krankenhaus hat
    progresstimer_percent_t needrestinhospitalinpercent;
};

/// GameCreature Genetik
struct CreatureGeneComponent {
    /// Creature Geschlecht
    data::CreatureGender gender = data::CreatureGender::None;

    /// Nummer der Generation
    counter_t generationnr = 0u;

    data::bmi_t min_bmi = 0.0;      ///< minimal BMI
    data::bmi_t ideal_bmi = 0.0;    ///< Ideal BMI
    data::bmi_t max_bmi = 0.0;      ///< maximal BMI
    data::bodysize_t max_bodysize = 0.0; ///< maximale Körpergröße
    data::bodymass_t bodymass = 0.0;     ///< Körpermasse
    data::weight_t min_weight = 0.0;   ///< minimal Gewicht
    data::weight_t max_weight = 0.0;   ///< maximal Gewicht

    /// benötigte Müdigkeit damit es Schlafen gehen will
    progresstimer_percent_t cangosleep_at_tired = 0.0;

    /// maximale Haufen die es aufeinmal legen kann
    counter_t max_poopstack = 0u;

    data::percent_rate_t ill_by_max_poopstack_rate = 0;
    progresstimer_percent_t poop_at_digestion_value = 0.0;


    /// Mehr Eigenschaften pro CreatureLevel
    earr::enum_array<data::CreatureLevel, CreatureGenePerEvolution>
        perevolution;


    /// Maximale Lebensdauer (Lebenserwartung)
    lifetime_t totalmaxlifetime;
};

} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREGENE_H_
