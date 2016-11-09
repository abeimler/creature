#include "doctest.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreaturePsyche Component") {
    gameentity::CreatureEntityCreator creaturecreator;

    auto psyche = creaturecreator.createCreaturePsyche();

    SUBCASE("Luck is set") { CHECK(psyche.luck >= 100.0f); }

    SUBCASE("Disciplin is set") { CHECK(psyche.disc >= 100.0f); }
}
