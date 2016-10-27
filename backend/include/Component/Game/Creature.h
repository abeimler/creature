#ifndef COMPONENT_GAME_CREATURE_H_
#define COMPONENT_GAME_CREATURE_H_

#include "Data/Creature.h"
#include "Data/CreatureBattlerStatus.h"
#include "Data/Food.h"

#include "Component/DateTimer.h"

#include "Component/Game/CreatureBattler.h"
#include "Component/Game/ProgressTimer.h"
#include "Component/Game/ProgressTimerCallback.h"
#include "Component/Game/ProgressTimerIncrement.h"

#include "Component/Game/CreatureGene.h"
#include "Component/Game/CreatureMemory.h"
#include "Component/Game/EvolutionTrakingInfos.h"

#include "Component/Game/CreatureProgressTimers.h"

namespace gamecomp {

/// Grund des Todes
BETTER_ENUM(CauseOfDeath, size_t, BEGIN,
            Alive = BEGIN,     ///< Noch am leben
            Starved,           ///< Verhungert
            Thirst,            ///< Verdurstet
            StrongUnderweight, ///< starkes Untergewicht
            Hurt,              ///< Verletzung
            Ill,               ///< Krankheit
            Senility,          ///< Altersschwäche
            ZeroHP,            ///< keine HP mehr
            Unknown,           ///< Unbekannt
            END)

/// Grund des Weglaufens
BETTER_ENUM(CauseOfRunAway, size_t, BEGIN,
            NotRunAway = BEGIN, ///< Nicht weggelaufen
            Starved,            ///< Verhungert
            Unhappy,            ///< Unglücklich
            END)


struct CreatureHungerComponent {
    StarvationPhase starvationphase = StarvationPhase::None; ///< Hungerphasen
    int digestionheap = 0; ///< Anzahl der Haufen (nicht weggeräumt)
};

struct CreatureSleepComponent {
    bool lighton = false;    ///< Schlaflicht ist an/aus (gut/schlecht schlafen)
    bool cangosleep = false; ///< Creature ist bereit Schlafen zu gehen
    bool havegoodsleep = false; ///< hat guten schlaf
};

struct CreatureTrainingComponent {
    /// Einfacher Timer um zu ermitteln wie lang schon trainiert wird
    comp::DateTimer trainingtimer;

    std::chrono::milliseconds traintime; ///< Trainigszeit

    /// Trainings Zeitpunkt
    data::CreatureTrainTime creaturetraintime = data::CreatureTrainTime::Noon;

    /// Zeitpunkt des Trainingsstart
    std::chrono::system_clock::time_point start_train;

    /// Zeitpunkt des Trainingsende
    std::chrono::system_clock::time_point end_train;

    /// Attribute die Trainiert werden sollen
    earr::enum_array<data::Attribute, bool> trainattrs;

    /// Attribute die zulezt Trainiert wurden
    earr::enum_array<data::Attribute, bool> lasttrainattrs;

    /// Werte die beim letzen Training erreicht wurden
    earr::enum_array<data::Attribute, int> attrparam_aftertrain;

    /// Werte vor dem letzen Training
    earr::enum_array<data::Attribute, int> attrparam_befortrain;

    /// Anzahl der Trainingseinheiten an bestimmten Zeiten
    earr::enum_array<data::CreatureTrainTime, int> trainingcounter;

    /// Zeitpunkt an den am meisten Trainiert wurde
    data::CreatureTrainTime mosttraintime = data::CreatureTrainTime::Noon;
};

struct CreatureBodilyStateComponent {
    int hurtcount = 0; ///< Anzahl der überstanden Verletzungen
    int illcount = 0;  ///< Anzahl der überstanden Krankheiten
};

struct CreatureBodyComponent {
    double weight = 0.0;   ///< Gewicht in g/kg
    double bodysize = 0.0; ///< Körpergröße in m
    double bmi = 0.0;      ///< Body Mass Index
    double calories = 0.0; ///< Eated Calories
};

struct CreaturePsycheComponent {
    double luck = 0.0; ///< Glück
    double disc = 0.0; ///< Disziplin
};

struct CreatureEvolveComponent {
    /// Evolution-Traking Info von den Vorstufen
    std::deque<std::string> preevolution_creature_name;

    /// Evolution-Traking Zusatzinfo
    std::deque<EvolutionTrakingInfo> evolutiontrakinginfo;
};

struct CreatureLifeComponent {
    std::string name; ///< Creaturename

    /// Creature level
    data::CreatureLevel creaturelevel = data::CreatureLevel::Egg;

    /// circadiane Rhythmik, Schlaf-Wach-Rhythmus
    data::CreatureCircadianRhythm creaturecircadianrhythm =
        data::CreatureCircadianRhythm::Unknown;

    /// Todesursache
    CauseOfDeath causeofdeath = CauseOfDeath::Alive;

    /// Grund fürs weglaufen
    CauseOfRunAway causeofrunaway = CauseOfRunAway::NotRunAway;

    /// true, es ist geboren/geschlüpft ist
    bool born = false;

    /// true, BattlerStatus ist Tot und die Creature vollkommen tot
    bool isdead = false;

    /// Maximale Lebensdauer (Lebenserwartung)
    std::chrono::milliseconds maxlifetime;

    /// Zeit die einem Alter entspricht
    std::chrono::milliseconds ageingtime;

    /// Alter, lifetime/ageingtime
    int age = 0;

    /// Geburtstag/Schlüpftag
    std::chrono::system_clock::time_point birthday;

    /// Lebensdauer
    std::chrono::milliseconds lifetime;

    /// Zeit in der die Creature geupdated werden sollte
    std::chrono::milliseconds needrefreshin_ms;

    /// Vorheriges Level,
    /// zum überprüfen falls ein LevelUp erreicht wurde
    int oldlevel = 0;

    /// hat Creature bestimmten Status
    earr::enum_array<data::CreatureStatus, bool> hasstatus;

    /// Creature ist beschaeftigt
    bool isbusy = false;

    /// Gelangweilt
    bool bored = false;

    /// Bereicht sich zu entwickeln
    bool readytoevolve = false;

    /// is fähig etwas zu essen
    bool caneat = false;

    /// is fähig etwas zu trinken
    bool candrink = false;

    /// is fähig etwas zu trainieren
    bool cantrain = false;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_CREATURE_H_
