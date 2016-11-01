#include "Entity/Game/EntityGameTestHelper.h"

gamecomp::CreatureBattlerGeneComponent EntityGameTestHelper::make_CreatureBattlerGene_withValues() {
    gamecomp::CreatureBattlerGeneComponent gene;

    for (auto& boni : gene.boniattrinflation) {
        boni = 5;
    }
    for (auto& boni : gene.boniattrfactor) {
        boni = 2.0f;
    }

    return gene;
}
