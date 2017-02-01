#ifndef COMPONENT_GAME_CREATUREMEMORY_H_
#define COMPONENT_GAME_CREATUREMEMORY_H_


#include "Component/Game/Basic.h"

namespace gamecomp {

/// GameCreature Aktivitäten
BETTER_ENUM(CreatureActivity, size_t, Noting,
            BEGIN = Noting, ///< Nichts tun
            Bored,          ///< gelangweilt

            Born,    ///< Wurde gerade Geboren/Geschlüpft
            Hurt,    ///< Wurde gerade Verletzt
            Ill,     ///< Wurde gerade Krank
            RunAway, ///< Is gerade weggelaufen
            ComeBackFromRunAway, ///< is gerade vom weglaufen zurück gekommen

            Asleep,             ///< eingeschlafen
            AsleepWithLight,    ///< eingeschlafen mit Licht an
            AsleepWithoutLight, ///< eingeschlafen mit Licht aus

            WakeUp,     ///< aufgewacht
            WakeUpGood, ///< aufgewacht mit guten Schlaf
            WakeUpBad,  ///< aufgewacht mit schlechten Schlaf

            StartTraining,    ///< hat mit den Training begonnen
            CancelTraining,   ///< Training wurde Abgebrochen
            FinishedTraining, ///< Training wurde beendet
            WillNotTrain,     ///< Will nicht trainieren

            GoToHospital,      ///< Krankenhaus Besuch
            HospitalVisitGood, ///< Guter Krankenhaus Besuch
            HospitalVisitBad,  ///< schlechter Krankenhaus Besuch


            /// Hat sich gerade Entwickelt (gute Entwicklung)
            EvolveGood,

            /// Hat sich gerade Entwickelt (schlecht Entwicklung)
            EvolveBad,

            Eat,        ///< Hat gerade etwas gegessen
            WillNotEat, ///< Will nicht Essen

            Drink,        ///< Hat gerade etwas getrunken
            WillNotDrink, ///< Will nicht trinken

            MakePoop,       ///< Hat gerade ein Haufen gelegt
            MakePoopInToilet, ///< Hat gerade ein Haufen gelegt (auf der
            /// Toilette)
            MakeNoPoop,
            END)


/// Mittelzeit Erinnerung der GameCreature (Bei Timer abgelaufen
/// verbessen)
struct CreatureActivityShort {
    /// Erinnerungswert, > 0 : gute Erinnerung, < 0 : schlechte Erinnerung
    memory_value_t value = 0;
};


struct CreatureMemoryDeepMemory {
    CreatureActivity activity;

    /// Mittlezeitgedächnis
    CreatureActivityShort medium_memory;

    /// Langzeitgedächnis
    deep_memory_value_t long_memory = 0.0;

    /// Erinnerungswert als factor
    memory_factor_t goodmemoryfactor = 1.0;
    memory_factor_t badmemoryfactor = 1.0;
};

/// GameCreature Gedächnis
struct CreatureMemoryComponent {
    /// Maximaleanzahl Erinnerung im Kurzzeitgedächnis
    size_t max_short_memorysize = 0;

    /// Kurzzeitgedächnis
    std::vector<CreatureActivity> short_memory;

    /// Mittlezeitgedächnis, Langzeitgedächnis und weiteres zu jeder Aktivität
    std::vector<CreatureMemoryDeepMemory> deep_memory;
};


/// GameCreature Persönlichkeit
struct CreaturePersonalityComponent {
    std::string nickname;

    boolean_t housebroken = false;

    /// Erinnerung an die Geburt
    deep_memory_value_t rememberborn = 1.0;

    /// oftmals Verletzt oder Krank
    deep_memory_value_t oftenhurtill = 1.0;

    /// Erinnerung an Weglaufen
    deep_memory_value_t rememberrunaway = 1.0;

    /// Erinnerung an Krankenaus besuch
    deep_memory_value_t rememberhospitalvisit = 1.0;

    /// Likes
    deep_memory_value_t likesleep = 1.0;
    deep_memory_value_t likehospital = 1.0;
    deep_memory_value_t liketraining = 1.0;
    deep_memory_value_t likeeat = 1.0;
    deep_memory_value_t likedrink = 1.0;

    deep_memory_value_t remembergototoilet = 1.0;

    /// Langeweile
    deep_memory_value_t bored = 1.0;
};


} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREMEMORY_H_
