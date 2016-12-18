#ifndef COMPONENT_GAME_EVOLUTIONTRAKINGINFOS_H_
#define COMPONENT_GAME_EVOLUTIONTRAKINGINFOS_H_

#include "Data/Creature.h"

#include "Component/DateTimer.h"

#include "Component/Game/Basic.h"

namespace gamecomp {

/// Rückgabewert von evolution
BETTER_ENUM(EvolutionStatus, size_t, Succ,
            BEGIN = Succ,      ///< Erfolgreich entwickelt
            DeadOrNotReady,    ///< Tot, nicht Bereit oder Beschäftigt
            NoneNextCreatures, ///< keine Entwicklungen vorhanden
            Fail,              ///< keine Entwicklung geschafft
            END)

/// Creature Evolution Info
struct EvolutionTrakingInfoDetail {
    /// Zeitpunkt der Entwicklung
    std::chrono::system_clock::time_point datetime;

    /// Lebenszeit der Entwicklung
    lifetime_t lifetime;
};

/// Evolution-Traking Infos
struct EvolutionTrakingInfo {
    std::string oldcreature_name;
    std::string newcreature_name;

    EvolutionTrakingInfoDetail evolutiontrakinginfodetail;


    EvolutionTrakingInfo() = default;

    EvolutionTrakingInfo(const data::Creature& p_oldcreature, const data::Creature& p_newcreature, const EvolutionTrakingInfoDetail& p_evolutiontrakinginfodetail)
        : oldcreature_name(p_oldcreature.getName()),
          newcreature_name(p_newcreature.getName()),
          evolutiontrakinginfodetail(p_evolutiontrakinginfodetail) {}
    
    EvolutionTrakingInfo(std::string p_oldcreature, std::string p_newcreature, const EvolutionTrakingInfoDetail& p_evolutiontrakinginfodetail)
        : oldcreature_name(p_oldcreature),
          newcreature_name(p_newcreature),
          evolutiontrakinginfodetail(p_evolutiontrakinginfodetail) {}
};
} // namespace gamecomp

#endif // COMPONENT_GAME_EVOLUTIONTRAKINGINFOS_H_
