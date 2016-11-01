#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatureMemory Component") {
    gameentity::CreatureCreator creaturecreator;

    auto memory = creaturecreator.createCreatureMemory();

    SUBCASE("maxShortTermMemorySize is set") {
        CHECK(memory.max_short_memorysize != 0);
    }

    SUBCASE("maxShortTermMemorySize is in right range (max + variance)") {
        int maxsize = static_cast<int>(creaturecreator.getMaxShortMemorySize());
        int variance = creaturecreator.getMaxShortMemorySizeVariance();

        int lower_range = maxsize - variance;
        int higher_range = maxsize + variance;

        SUBCASE("maxShortMemorySize is in right lower range") {
            CHECK(static_cast<int>(memory.max_short_memorysize) >=
                    lower_range);
        }

        SUBCASE("maxShortMemorySize is in right upper range") {
            CHECK(static_cast<int>(memory.max_short_memorysize) <=
                    higher_range);
        }
    }
}
