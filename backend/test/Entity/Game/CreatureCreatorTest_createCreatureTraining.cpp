#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatureTraining Component") {
    gameentity::CreatureCreator creaturecreator;

    auto training = creaturecreator.createCreatureTraining();

    SUBCASE("trainingCounter Noon is set, 0") {
        CHECK(0 == earr::enum_array_at(training.trainingcounter,
                                        +data::CreatureTrainTime::Noon));
    }

    SUBCASE("trainAttrs MaxHP is set, false") {
        CHECK(false == earr::enum_array_at(training.trainattrs,
                                        +data::Attribute::MaxHP));
    }
    SUBCASE("lastTrainAttrs MaxHP is set, false") {
        CHECK(false == earr::enum_array_at(training.lasttrainattrs,
                                        +data::Attribute::MaxHP));
    }

    SUBCASE("attrParamBeforTrain MaxHP is set, false") {
        CHECK(0 == earr::enum_array_at(training.attrparam_befortrain,
                                        +data::Attribute::MaxHP));
    }
    SUBCASE("attrParamAfterTrain MaxHP is set, false") {
        CHECK(0 == earr::enum_array_at(training.attrparam_aftertrain,
                                        +data::Attribute::MaxHP));
    }
}
