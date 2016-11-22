#include "doctest.h"

#include "Entity/Game/CreatureEntityCreator.h"

#include "EntityGameTestHelper.h"


TEST_CASE("setup CreatureProgressTimers with Gene") {
    CreatureTestData creatureTestData;
    gameentity::CreatureEntityCreator creaturecreator;
    gameentity::CreatureBattlerCreator creaturebattler_creator;

    auto time = creatureTestData.make_time_point_01_01_2000();

    auto creature = creatureTestData.make_DataCreature();
    auto creature_data = creaturebattler_creator.createCreatureData(creature);
    auto creature_battler = creaturebattler_creator.createCreatureBattler();
    auto gene = creaturecreator.createCreatureGene(creature_data);
    auto life = creaturecreator.createCreatureLife(creature_data, time,
                                                   creature_battler, gene);
    auto body = creaturecreator.createCreatureBody(creature_data, gene);

    auto timers = creaturecreator.createCreatureProgressTimers(time, 1.0f);

    creaturecreator.setupCreatureProgressTimers(timers, creature_data, life,
                                                gene, body);

    SUBCASE("Growing Timer is set") {
        auto& growing_timer = earr::enum_array_at(
            timers.increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);

        SUBCASE("addvalue_per_percent is set") {
            CHECK(growing_timer.addvalue_per_percent > 0.0f);
        }
    }

    SUBCASE("IllbyOverweight Timer is set") {
        auto& illbyOverweight_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::IllbyOverweight);

        SUBCASE("is endless") { CHECK(illbyOverweight_timer.isendless); }
    }

    SUBCASE("LostWeightTimerHungry Timer is set") {
        auto& lostweighthungry_timer = earr::enum_array_at(
            timers.increment,
            +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerHungry);

        SUBCASE("is endless") { CHECK(lostweighthungry_timer.isendless); }
    }

    SUBCASE("LostWeightTimerThirsty Timer is set") {
        auto& lostweighthirsty_timer = earr::enum_array_at(
            timers.increment,
            +gamecomp::CreatureProgressTimerIncrement::LostWeightTimerThirsty);

        SUBCASE("is endless") { CHECK(lostweighthirsty_timer.isendless); }
    }

    SUBCASE("LostCalories Timer is set") {
        auto& lostcalories_timer = earr::enum_array_at(
            timers.increment,
            +gamecomp::CreatureProgressTimerIncrement::LostCalories);

        SUBCASE("is endless") { CHECK(lostcalories_timer.isendless); }
    }

    SUBCASE("GainWeightCalories Timer is set") {
        auto& gainweightcalories_timer = earr::enum_array_at(
            timers.increment,
            +gamecomp::CreatureProgressTimerIncrement::GainWeightCalories);

        SUBCASE("is endless") { CHECK(gainweightcalories_timer.isendless); }
    }

    SUBCASE("HurtToDead Timer is set") {
        auto& hurtToDead_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::HurtToDead);

        SUBCASE("is endless") { CHECK(hurtToDead_timer.isendless); }
    }

    SUBCASE("IllToDead Timer is set") {
        auto& illToDead_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::IllToDead);

        SUBCASE("is endless") { CHECK(illToDead_timer.isendless); }
    }

    SUBCASE("Digestion Timer is set") {
        auto& digestion_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::Digestion);

        SUBCASE("is endless") { CHECK(digestion_timer.isendless); }
    }

    SUBCASE("PauseDigestionHungry Timer is set") {
        auto& pauseDigestionHungry_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::PauseDigestionHungry);

        SUBCASE("is endless") { CHECK(pauseDigestionHungry_timer.isendless); }
    }

    SUBCASE("FullDigestionHeap Timer is set") {
        auto& fullDigestionHeap_timer = earr::enum_array_at(
            timers.callback,
            +gamecomp::CreatureProgressTimerCallback::FullDigestionHeap);

        SUBCASE("is endless") { CHECK(fullDigestionHeap_timer.isendless); }
    }

    SUBCASE("Hungry Timer waittime is set") {
        std::chrono::milliseconds timer_waittime = gameentity::
            CreatureEntityCreator::getCreatureProgressTimersWaitTime(
                timers.timer, +gamecomp::CreatureProgressTimer::Hungry,
                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime =
            earr::enum_array_at(perevolution.waittime.timer,
                                +gamecomp::CreatureProgressTimer::Hungry);

        CHECK(timer_waittime == gene_waittime);
    }

    SUBCASE("Digestion Timer waittime is set") {
        std::chrono::milliseconds timer_waittime = gameentity::
            CreatureEntityCreator::getCreatureProgressTimersWaitTime(
                timers.callback,
                +gamecomp::CreatureProgressTimerCallback::Digestion,
                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime = earr::enum_array_at(
            perevolution.waittime.callback,
            +gamecomp::CreatureProgressTimerCallback::Digestion);

        CHECK(timer_waittime == gene_waittime);
    }

    SUBCASE("Growing Timer waittime is set") {
        std::chrono::milliseconds timer_waittime = gameentity::
            CreatureEntityCreator::getCreatureProgressTimersWaitTime(
                timers.increment,
                +gamecomp::CreatureProgressTimerIncrement::Growing,
                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime = earr::enum_array_at(
            perevolution.waittime.increment,
            +gamecomp::CreatureProgressTimerIncrement::Growing);


        CHECK(timer_waittime == gene_waittime);
    }

    SUBCASE("Starvation Timer waittime is set") {
        std::chrono::milliseconds timer_waittime = gameentity::
            CreatureEntityCreator::getCreatureProgressTimersWaitTime(
                timers.starvation, +gamecomp::StarvationPhase::Phase1,
                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime =
            earr::enum_array_at(perevolution.waittime.starvation,
                                +gamecomp::StarvationPhase::Phase1);


        CHECK(timer_waittime == gene_waittime);
    }

    SUBCASE("ShortMemoryTerm Timer waittime is set") {
        auto& shortterm_memory_timer =
            earr::enum_array_at(timers.memory, +gamecomp::CreatureActivity::Eat)
                .shortterm;
        std::chrono::milliseconds timer_waittime =
            earr::enum_array_at(shortterm_memory_timer.base.waittime,
                                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime =
            earr::enum_array_at(perevolution.waittime.shorttermmemory,
                                +gamecomp::CreatureActivity::Eat);


        CHECK(timer_waittime == gene_waittime);
    }

    SUBCASE("MediumMemoryTerm Timer waittime is set") {
        auto& mediumterm_memory_timer =
            earr::enum_array_at(timers.memory, +gamecomp::CreatureActivity::Eat)
                .mediumterm;
        std::chrono::milliseconds timer_waittime =
            earr::enum_array_at(mediumterm_memory_timer.base.waittime,
                                creatureTestData.CREATURELEVEL);


        auto& perevolution = earr::enum_array_at(
            gene.perevolution, creatureTestData.CREATURELEVEL);

        std::chrono::milliseconds gene_waittime =
            earr::enum_array_at(perevolution.waittime.mediumtermmemory,
                                +gamecomp::CreatureActivity::Eat);

        CHECK(timer_waittime == gene_waittime);
    }
}
