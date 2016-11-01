#include "doctest.h"

#include "Entity/Game/CreatureCreator.h"

#include "Entity/Game/EntityGameTestHelper.h"


TEST_CASE("create CreatureGene Component with DataCreature") {
    gameentity::CreatureCreator creaturecreator;
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto creature = CreatureTestData::make_DataCreature();
    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto gene = creaturecreator.createCreatureGene(creature_data);


    SUBCASE("Generation Nr. is 1") { CHECK(1 == gene.generationnr); }


    SUBCASE("BodyMass is set") {
        CHECK(gene.bodymass != doctest::Approx(0.0f).epsilon(0.01));
    }

    SUBCASE("Max BodySize is set") {
        CHECK(gene.max_bodysize ==
                doctest::Approx(creature.getMaxBodySize()).epsilon(0.01));
    }

    SUBCASE("Min BodyWeight is set") {
        CHECK(gene.min_weight ==
                doctest::Approx(creature.getMinWeight()).epsilon(0.01));
    }

    SUBCASE("Max BodyWeight is set") {
        CHECK(gene.max_weight ==
                doctest::Approx(creature.getMaxWeight()).epsilon(0.01));
    }


    SUBCASE("totalMaxLifeTime is set") {
        CHECK(gene.totalmaxlifetime >= creaturecreator.getMinTotalLifetime());
    }

    SUBCASE("needSleepinPercent is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.needsleepinpercent > 0);
    }

    SUBCASE("needRestInHospitalinPercent is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.needrestinhospitalinpercent > 0);
    }


    SUBCASE("maxHungryOverlayvalueInTraining is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.max_hungryoverlay_intraining > 0.0f);
    }

    SUBCASE("maxThirstyOverlayvalueInTraining is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.max_thirstyoverlay_intraining > 0.0f);
    }

    SUBCASE("maxTiredOverlayvalueInTraining is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.max_tiredoverlay_intraining > 0.0f);
    }


    SUBCASE("minTrainTime is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.min_trainitime > std::chrono::seconds::zero());
    }

    SUBCASE("middleTrainTime is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.middle_trainitime > std::chrono::seconds::zero());
    }

    SUBCASE("goodTrainTime is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.training.good_trainitime > std::chrono::seconds::zero());
    }

    SUBCASE("runAwayTime by unluck is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        CHECK(perevolution.runawaytime_unluck > std::chrono::seconds::zero());
    }

    SUBCASE("ProgressTimer Hungry is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.timer, +gamecomp::CreatureProgressTimer::Hungry);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }

    SUBCASE("CallbackProgressTimer Digestion is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.callback, +gamecomp::CreatureProgressTimerCallback::Digestion);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }

    SUBCASE("ProgressTimerIncrement LostWeightTimerHungry is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.increment, +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }

    SUBCASE("ProgressTimerCallback Startvation Phase1 is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.starvation, +gamecomp::StarvationPhase::Phase1);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }

    SUBCASE("ProgressTimerCallback ShortTermMemory Eat is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.shorttermmemory, +gamecomp::CreatureActivity::Eat);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }

    SUBCASE("ProgressTimerCallback MediumTermMemory Eat is set") {
        auto& perevolution = earr::enum_array_at(gene.perevolution, CreatureTestData::CREATURELEVEL);
        const auto& waittime = earr::enum_array_at(perevolution.waittime.mediumtermmemory, +gamecomp::CreatureActivity::Eat);
        
        CHECK(waittime > std::chrono::seconds::zero());
    }
}
