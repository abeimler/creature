#ifndef COMPONENT_GAME_CREATUREBATTLERGENE_H_
#define COMPONENT_GAME_CREATUREBATTLERGENE_H_

#include "Component/Game/Basic.h"
#include "Component/Game/Battler.h"

namespace gamecomp {

/// Battler Gene
struct CreatureBattlerGeneComponent {
    /// Boni Infaltion value of Attribute
    earr::enum_array<data::Attribute, data::attr_t> boniattrinflation;

    /// Boni Factor of Attribute
    earr::enum_array<data::Attribute, data::attr_factor_t> boniattrfactor;
};
} // namespace gamecomp

#endif // COMPONENT_GAME_CREATUREBATTLERGENE_H_
