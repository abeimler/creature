#ifndef COMPONENT_GAME_CREATUREPROGRESSTIMERS_H_
#define COMPONENT_GAME_CREATUREPROGRESSTIMERS_H_

#include "Data/Creature.h"

#include "Component/DateTimer.h"

#include "Component/Game/ProgressTimer.h"
#include "Component/Game/ProgressTimerCallback.h"
#include "Component/Game/ProgressTimerIncrement.h"

#include "Component/Game/CreatureMemory.h"

namespace gamecomp {

/// Hungerphase
BETTER_ENUM(StarvationPhase, size_t, None,
            BEGIN = None, ///< Nichts
            Phase1,       ///< Hungern
            Phase2,       ///< Weglaufen
            Phase3,       ///< Unglücklich wieder kommen
            Phase4,       ///< Weglaufen
            Phase5,       ///< Krank,Verletzt und Unglücklich wieder kommen
            Phase6,       ///< Tot
            END)

BETTER_ENUM(CreatureProgressTimer, size_t, Hungry,
            BEGIN = Hungry, ///< Prozess für Hunger
            Thirsty,        ///< Prozess für Durst
            Tired,          ///< Verlauf für Müdigkeit
            Training,       ///< Verlauf für Training
            Evolution,      ///< Verlauf für Entwicklung
            RunAway,        ///< Verlauf für WegLauf-Phase
            END)

BETTER_ENUM(
    CreatureProgressTimerCallback, size_t, Digestion,
    BEGIN = Digestion,    ///< Prozess für die Verdauung
    PauseDigestionHungry, ///< Pausiert Verdauung wenn Hunger zu lang geht
    FullDigestionHeap,    ///< wenn X haufen nicht aufgeräumt wurden, Krankheit
    IllbyOverweight,      ///< Timer für Krankheit durch Übergewicht
    GoSleep,              ///< Timer fürs einschlafen
    Inhospital,           ///< Verlauf für Krankenhausbesuch
    HurtToDead,           ///< Tod der durch die Verletzung ausgelöst wurde
    IllToDead,            ///< Tod der durch eine Krankheit ausgelöst wurde
    Unhappy,              ///< bei Glück == 0
    RunAwayUnhappy,       ///< Weglaufen bei Glück == 0 und nach Unhappy-Timer
    Bored,                ///< wenn langezwit nichts mehr gemacht wurde
    END)

BETTER_ENUM(
    CreatureProgressTimerIncrement, size_t, LostWeightTimerHungry,
    BEGIN = LostWeightTimerHungry, ///< normaler Gewichtsverlust(Hunger) in einer bestimmten Zeit
    LostWeightTimerThirsty, ///< normaler Gewichtsverlust(Durst) in einer
                            /// bestimmten Zeit
    LostCalories,           ///< Calories Verbrauch in einer bestimmten Zeit
    GainWeightCalories,     ///< normaler Gewichtszunahme bei zu vielen Kalorien
    GoodSleep,              ///< Verlauf für den guten Schlaf
    BadSleep,               ///< Verlauf für den schlechten Schlaf
    Rest,                   ///< Verlauf für normales Ausruhen
    RestHospital,           ///< Verlauf für Ausruhen im Krankenhaus
    HurtLostHP, ///< Regelmässiges verlieren von HP durch die Verletzung
    Growing,    ///< Verlauf für deb Wachstum
    END)

struct CreatureProgressTimersMemory {
    ProgressTimerCallback shortterm;
    ProgressTimerCallback mediumterm;
};

struct CreatureProgressTimersComponent {
    comp::DateTimer lifetimer; ///< Lebenszeit (Alter)

    earr::enum_array<CreatureProgressTimer, ProgressTimer> timer;
    earr::enum_array<CreatureProgressTimerCallback, ProgressTimerCallback>
        callback;
    earr::enum_array<CreatureProgressTimerIncrement, ProgressTimerIncrement>
        increment;

    /// Timer in der Hungerphase (für die Hungerphasen)
    earr::enum_array<StarvationPhase, ProgressTimerCallback> starvation;

    // Timer für das Gedächnis
    earr::enum_array<CreatureActivity, CreatureProgressTimersMemory> memory;

    data::CreatureLevel creaturelevel = data::CreatureLevel::Egg;
};

} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREPROGRESSTIMERS_H_
