#ifndef COMPONENT_GAME_CREATUREMEMORY_H_
#define COMPONENT_GAME_CREATUREMEMORY_H_

#include "Component/Basic.h"

namespace gamecomp {

/// GameCreature Aktivitäten
BETTER_ENUM(CreatureActivity, size_t, BEGIN,
            Noting = BEGIN, ///< Nichts tun
            Bored,          ///< gelangweilt

            Born,    ///< Wurde gerade Geboren/Geschlüpft
            Hurt,    ///< Wurde gerade Verletzt
            Ill,     ///< Wurde gerade Krank
            RunAway, ///< Is gerade weggelaufen

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

            MakeDigestionHeap,       ///< Hat gerade ein Haufen gelegt
            MakeDigestionHeapToilet, ///< Hat gerade ein Haufen gelegt (auf der
            /// Toilette)
            END)

/// Mittelzeit Erinnerung der GameCreature (Bei Timer abgelaufen
/// verbessen)
struct CreatureActivityShort {
    /// Erinnerungswert, > 0 : gute Erinnerung, < 0 : schlechte Erinnerung
    int value = 0;
};


struct CreatureMemoryDeepMemory {
    CreatureActivity activity;

    /// Mittlezeitgedächnis
    CreatureActivityShort medium_memory;

    /// Langzeitgedächnis
    double long_memory = 0.0;

    /// Erinnerungswert als factor
    double goodmemoryfactor = 1.0;
    double badmemoryfactor = 1.0;
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
    /// Erinnerung an die Geburt
    double rememberborn = 1.0;

    /// oftmals Verletzt oder Krank
    double oftenhurtill = 1.0;

    /// Erinnerung an Weglaufen
    double rememberrunaway = 1.0;

    /// Erinnerung an Krankenaus besuch
    double rememberhospitalvisit = 1.0;

    /// Likes
    double likesleep = 1.0;
    double likehospital = 1.0;
    double liketraining = 1.0;
    double likeeat = 1.0;
    double likedrink = 1.0;

    double remembergototoilet = 1.0;

    /// Langeweile
    double bored = 1.0;
};


} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREMEMORY_H_
