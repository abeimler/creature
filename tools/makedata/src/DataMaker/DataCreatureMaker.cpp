#include "DataMaker/DataCreatureMaker.h"

namespace datamaker {

DataCreatureMaker::DataCreatureMaker() {}


int DataCreatureMaker::getLeveltoEvol(data::CreatureLevel creatureLevel) {
    int lvl = 1;
    switch (creatureLevel) {
        case data::CreatureLevel::Child:
            lvl = 2;
            break;
        case data::CreatureLevel::Adult:
            lvl = 10;
            break;
        case data::CreatureLevel::Perfect:
            lvl = 21;
            break;
        case data::CreatureLevel::Ultimate:
            lvl = 26;
            break;
        case data::CreatureLevel::Baby:
        case data::CreatureLevel::Baby2:
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::END:
            lvl = 1;
            break;
    }

    return lvl;
}

void DataCreatureMaker::initBeforData(
    const std::vector<std::string>& elements, const resists_t& elements_resists,
    const std::map<std::string, std::vector<std::string>>& types) {
    std::cout << "make Elements" << '\n';
    this->makeElements(elements, elements_resists);
    std::cout << "make Elements done" << '\n';

    std::cout << "make CreatureTypes" << '\n';
    this->makeTypes(types);
    std::cout << "make CreatureTypes done" << '\n';

    std::cout << "make CreatureStatuses" << '\n';
    this->makeStatuses();
    std::cout << "make CreatureStatuses done" << '\n';
}

void DataCreatureMaker::initAfterData() {
    std::cout << "make CreatureStarter" << '\n';
    this->makeStarter();
    std::cout << "make CreatureStarter done" << '\n';
}


void DataCreatureMaker::makeDataCreature(data::Creature& data_creature, std::string name, DataCreatureClass cls, 
    const rand_tuple_t& rand_attrBasis,
    const rand_tuple_t& rand_attrInfla, 
    const rand_tuple_t& rand_expBasis,
    const rand_tuple_t& rand_expInfla,
    data::CreatureCircadianRhythm creatureRhythm,
    data::CreatureLevel creatureLevel, std::string type_name,
    const std::vector<std::string>& elements, 
    const rand_tuple_t& minmax_lvl,
    int criticalHit, int hitRate, float evol_weight, float bodysize,
    DataCreatureGender gender) {


    data_creature.setName(name);

    auto type = this->datamanager_.findCreatureType(type_name);
    if(type){
        data_creature.setCreatureType(*type);
    } else {
        std::cout << "makeDataCreature: type " << type_name
                      << " not found" << '\n';
    }

    auto data_creature_attrBasis = data_creature.getAttrBasis();

    for (auto attr : earr::Enum<data::Attribute>()) {
        auto& attrBasis = earr::enum_array_at(data_creature_attrBasis, attr);

        attrBasis = util::random(std::get<0>(rand_attrBasis), std::get<1>(rand_attrBasis));

        attrBasis *= (attr == +data::Attribute::MaxHP)
                         ? util::random(40, 55) / 10.0f
                         : 1.0f;
        attrBasis *= (attr == +data::Attribute::MaxMP)
                         ? util::random(35, 45) / 10.0f
                         : 1.0f;
    }
    data_creature.setAttrBasis(data_creature_attrBasis);


    auto data_creature_attrInflation = data_creature.getAttrInflation();

    for (auto attr : earr::Enum<data::Attribute>()) {
        auto& attrInfla = earr::enum_array_at(data_creature_attrInflation, attr);

        attrInfla = util::random(std::get<0>(rand_attrInfla), std::get<1>(rand_attrInfla));

        attrInfla *= (attr == +data::Attribute::MaxHP)
                         ? util::random(40, 50) / 10.0f
                         : 1.0f;
        attrInfla *= (attr == +data::Attribute::MaxMP)
                         ? util::random(35, 45) / 10.0f
                         : 1.0f;
    }
    data_creature.setAttrInflation(data_creature_attrInflation);

    data_creature.setAttrBasis(data::Attribute::Exp,
                               util::random(std::get<0>(rand_expBasis), std::get<1>(rand_expBasis)));
    data_creature.setAttrInflation(data::Attribute::Exp,
                                   util::random(std::get<0>(rand_expInfla), std::get<1>(rand_expInfla)));

    data_creature.setCreatureCircadianRhythm(creatureRhythm);
    data_creature.setCriticalHitRate(criticalHit);
    data_creature.setHitRate(hitRate);
    data_creature.setCreatureLevel(creatureLevel);
    data_creature.setMinLvL(std::get<0>(minmax_lvl));
    data_creature.setMaxLvL(std::get<1>(minmax_lvl));
    data_creature.setStartLvL(1);

    data::EvolutionCondition data_creature_evolCondition =
        data_creature.getEvolCondition();
    data_creature_evolCondition.setWeight(evol_weight);

    float min_bodysize = bodysize * 0.7f;
    float max_bodysize = bodysize * 1.7f;
    data_creature.setBodySizeMin(min_bodysize);
    data_creature.setBodySizeMax(max_bodysize);


    float min_weight = evol_weight * 0.4f;
    float max_weight = evol_weight * 8;
    data_creature.setMinWeight(min_weight);
    data_creature.setMaxWeight(max_weight);


    // not used
    /*
    float min_bmi = 18;
    float ideal_bmi = 26;
    float max_bmi = 50;
    if (evol_weight >= 50 && bodysize >= 6) {
        min_bmi = 20;
        ideal_bmi = 33;
        max_bmi = 50;
    }
    */
    //float bodymass = this->creaturecreator_.getBodyMass(bodysize, evol_weight, min_weight, ideal_bmi, min_bmi, max_bmi);



    /*
     * None
     * Crepuscular  during twilight (i.e., dawn and dusk).
     * Diurnal      during the day and sleeping, or other inactivity, at night.
     * Nocturnal    activity during the night and sleeping during the day.
     * Variable
     * Unknown
     */

    data_creature_evolCondition.setTrainTimeEveryDay();
    switch (creatureRhythm) {
        case data::CreatureCircadianRhythm::Unknown:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, util::randomRate(90));
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, util::randomRate(90));
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, util::randomRate(90));
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, util::randomRate(90));
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, util::randomRate(90));
            break;
        case data::CreatureCircadianRhythm::None:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, true);
            break;
        case data::CreatureCircadianRhythm::Variable:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, true);
            break;
        case data::CreatureCircadianRhythm::Diurnal:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, false);
            break;
        case data::CreatureCircadianRhythm::Crepuscular:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, true);
            break;
        case data::CreatureCircadianRhythm::Nocturnal:
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Morning, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Noon, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::AfterNoon, false);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Evening, true);
            data_creature_evolCondition.setTrainTime(
                data::CreatureTrainTime::Night, true);
            break;
        case data::CreatureCircadianRhythm::END:
            break;
    }

    bool issettraintime = false;
    for (auto index : earr::Enum<data::CreatureTrainTime>()) {
        issettraintime |= data_creature_evolCondition.getTrainTime(index);
    }
    if (!issettraintime) {
        data_creature_evolCondition.setTrainTimeEveryDay();
    }

    int lvl = getLeveltoEvol(creatureLevel);
    switch (creatureLevel) {
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::Baby:
        case data::CreatureLevel::Baby2:
            data_creature_evolCondition.setTrainTimeEveryDay();
            break;
        case data::CreatureLevel::Child:
        case data::CreatureLevel::Adult:
        case data::CreatureLevel::Perfect:
        case data::CreatureLevel::Ultimate:
        case data::CreatureLevel::END:
            break;
    }

    // Entwicklern wenn bestimmte Stufe erreicht wurde
    switch (creatureLevel) {
        case data::CreatureLevel::Child:
            data_creature_evolCondition.setMustEvolveAtLevel(
                std::min<int>(lvl * 2.0f, data_creature.getMaxLvL()));
            break;
        case data::CreatureLevel::Adult:
            data_creature_evolCondition.setMustEvolveAtLevel(
                std::min<int>(lvl * 1.5f, data_creature.getMaxLvL()));
            break;
        case data::CreatureLevel::Perfect:
            data_creature_evolCondition.setMustEvolveAtLevel(
                std::min<int>(lvl, data_creature.getMaxLvL()));
            break;
        case data::CreatureLevel::Ultimate:
            data_creature_evolCondition.setMustEvolveAtLevel(
                std::min<int>(lvl, data_creature.getMaxLvL()));
            break;
        case data::CreatureLevel::Baby:
        case data::CreatureLevel::Baby2:
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::END:
            break;
    }

    /**
        Normal,
        Warrior,
        Knight,
        Starter,
        Thief,
        WarriorThief,
        Hunter,
        Wizard,
        Mage,
        Healer
    */
    attr_factor_t class_attr_factor;
    for (auto index : earr::Enum<data::Attribute>()) {
        class_attr_factor[index] = 1.0f;
    }

    switch (cls) {
        case DataCreatureClass::Normal:
            break;
        case DataCreatureClass::Warrior:
            class_attr_factor[+data::Attribute::MaxHP] = 1.023;
            class_attr_factor[+data::Attribute::MaxMP] = 0.802f;
            class_attr_factor[+data::Attribute::Atk] = 1.209f;
            class_attr_factor[+data::Attribute::Def] = 1.023f;
            class_attr_factor[+data::Attribute::Agi] = 1.267f;
            class_attr_factor[+data::Attribute::Int] = 0.837f;
            break;
        case DataCreatureClass::Knight:
            class_attr_factor[+data::Attribute::MaxHP] = 1.378f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.869f;
            class_attr_factor[+data::Attribute::Atk] = 1.029f;
            class_attr_factor[+data::Attribute::Def] = 0.913f;
            class_attr_factor[+data::Attribute::Agi] = 0.985f;
            class_attr_factor[+data::Attribute::Int] = 0.913f;
            break;
        case DataCreatureClass::Starter:
            class_attr_factor[+data::Attribute::MaxHP] = 0.948f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.991f;
            class_attr_factor[+data::Attribute::Atk] = 0.948f;
            class_attr_factor[+data::Attribute::Def] = 1.087f;
            class_attr_factor[+data::Attribute::Agi] = 1.201f;
            class_attr_factor[+data::Attribute::Int] = 0.913f;
            break;
        case DataCreatureClass::Thief:
            class_attr_factor[+data::Attribute::MaxHP] = 0.797f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.927f;
            class_attr_factor[+data::Attribute::Atk] = 0.797f;
            class_attr_factor[+data::Attribute::Def] = 0.913f;
            class_attr_factor[+data::Attribute::Agi] = 1.392f;
            class_attr_factor[+data::Attribute::Int] = 1.087f;
            break;
        case DataCreatureClass::WarriorThief:
            class_attr_factor[+data::Attribute::MaxHP] = 1.116f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.895f;
            class_attr_factor[+data::Attribute::Atk] = 1.302f;
            class_attr_factor[+data::Attribute::Def] = 1.023f;
            class_attr_factor[+data::Attribute::Agi] = 0.988f;
            class_attr_factor[+data::Attribute::Int] = 0.837f;
            break;
        case DataCreatureClass::Hunter:
            class_attr_factor[+data::Attribute::MaxHP] = 1.023f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.849f;
            class_attr_factor[+data::Attribute::Atk] = 1.116f;
            class_attr_factor[+data::Attribute::Def] = 1.023f;
            class_attr_factor[+data::Attribute::Agi] = 1.314f;
            class_attr_factor[+data::Attribute::Int] = 0.837f;
            break;
        case DataCreatureClass::Wizard:
            class_attr_factor[+data::Attribute::MaxHP] = 0.835f;
            class_attr_factor[+data::Attribute::MaxMP] = 1.265f;
            class_attr_factor[+data::Attribute::Atk] = 0.909f;
            class_attr_factor[+data::Attribute::Def] = 0.835f;
            class_attr_factor[+data::Attribute::Agi] = 0.973f;
            class_attr_factor[+data::Attribute::Int] = 1.091f;
            break;
        case DataCreatureClass::Mage:
            class_attr_factor[+data::Attribute::MaxHP] = 0.988f;
            class_attr_factor[+data::Attribute::MaxMP] = 1.042f;
            class_attr_factor[+data::Attribute::Atk] = 1.036f;
            class_attr_factor[+data::Attribute::Def] = 1.036f;
            class_attr_factor[+data::Attribute::Agi] = 0.970f;
            class_attr_factor[+data::Attribute::Int] = 0.964f;
            break;
        case DataCreatureClass::Healer:
            class_attr_factor[+data::Attribute::MaxHP] = 1.024f;
            class_attr_factor[+data::Attribute::MaxMP] = 0.988f;
            class_attr_factor[+data::Attribute::Atk] = 1.071f;
            class_attr_factor[+data::Attribute::Def] = 1.024f;
            class_attr_factor[+data::Attribute::Agi] = 0.845f;
            class_attr_factor[+data::Attribute::Int] = 1.024f;
            break;
    }

    for (auto index : earr::Enum<data::Attribute>()) {
        data_creature.setAttrBasis(index, data_creature.getAttrBasis(index) *
                                              class_attr_factor[index]);
        data_creature.setAttrInflation(index,
                                       data_creature.getAttrInflation(index) *
                                           class_attr_factor[index]);
    }

    if (creatureLevel > +data::CreatureLevel::Baby2) {
        for (auto index : earr::Enum<data::Attribute>()) {
            std::vector<int> attrs;
            attrs = this->creaturebattlercreator_.genAttrs<int>(data_creature,
                                                                index);

            int min =
                ((lvl < 5) ? (attrs[lvl] * 0.26) : (attrs[lvl] * 0.41)) + 1;
            int max =
                ((lvl < 5) ? (attrs[lvl] * 0.36) : (attrs[lvl] * 0.71)) + 1;

            if (creatureLevel > +data::CreatureLevel::Child) {
                min *= (index == +data::Attribute::MaxHP)
                           ? 1 + util::random(20, 25) / 1000.0f
                           : 1.0f;
                max *= (index == +data::Attribute::MaxHP)
                           ? 1 + util::random(25, 30) / 1000.0f
                           : 1.0f;
                min *= (index == +data::Attribute::MaxMP)
                           ? 1 + util::random(15, 20) / 1000.0f
                           : 1.0f;
                max *= (index == +data::Attribute::MaxMP)
                           ? 1 + util::random(20, 25) / 1000.0f
                           : 1.0f;
            } else {
                min *= (index == +data::Attribute::MaxHP)
                           ? 1 + util::random(25, 35) / 1000.0f
                           : 1.0f;
                max *= (index == +data::Attribute::MaxHP)
                           ? 1 + util::random(35, 40) / 1000.0f
                           : 1.0f;
                min *= (index == +data::Attribute::MaxMP)
                           ? 1 + util::random(20, 30) / 1000.0f
                           : 1.0f;
                max *= (index == +data::Attribute::MaxMP)
                           ? 1 + util::random(30, 35) / 1000.0f
                           : 1.0f;
            }

            data_creature_evolCondition.setAttr(index, util::random(min, max));
        }
        data_creature_evolCondition.setAttr(data::Attribute::Exp, 0);
    } else {
        for (auto index : earr::Enum<data::Attribute>()) {
            data_creature_evolCondition.setAttr(index, 0);
        }
    }

    data_creature.setEvolCondition(data_creature_evolCondition);


    calcElements(data_creature, elements);
    calcStatuses(data_creature);

    switch (gender) {
        case DataCreatureGender::None:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 0.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 0.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Hermaphrodite, 0.0f);
            break;
        case DataCreatureGender::Normal:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 50.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 50.0f);
            break;
        case DataCreatureGender::MoreMale:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 87.5f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 12.5f);
            break;
        case DataCreatureGender::MoreFemale:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 12.5f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 87.5f);
            break;
        case DataCreatureGender::OnlyMale:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 100.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 0.0f);
            break;
        case DataCreatureGender::OnlyFemale:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 0.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 100.0f);
            break;
        case DataCreatureGender::Hermaphrodite:
            data_creature.setGenderDistribution(
                data::CreatureGender::Male, 0.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Female, 0.0f);
            data_creature.setGenderDistribution(
                data::CreatureGender::Hermaphrodite, 100.0f);
            break;
    }

    saveCreature(data_creature);
}

void DataCreatureMaker::makeDataCreature(
    std::string name, std::string type, DataCreatureEvol state,
    DataCreatureClass cls, 
    const std::vector<std::string>& elements,
    data::CreatureCircadianRhythm creatureRhythm,
    data::CreatureLevel creatureLevel, float evol_weight, float bodysize,
    DataCreatureGender gender) {
    std::tuple<int, int> rand_attrBasis;
    std::tuple<int, int> rand_attrInfla;
    std::tuple<int, int> rand_expBasis;
    std::tuple<int, int> rand_expInfla;

    std::tuple<int, int> minmax_lvl;
    int criticalHit = 30;
    int hitRate = 90;

    auto creature_ptr = this->datamanager_.findCreature(name);
    if (!creature_ptr) {
        creature_ptr = std::make_shared<data::Creature>();
    }
    data::Creature& creature = *creature_ptr;

    data::EvolutionCondition creature_evolCondition =
        creature.getEvolCondition();

    switch (creatureLevel) {
        case data::CreatureLevel::Baby:
            rand_attrBasis = { 5, 10 };
            rand_attrInfla = { 3, 6 };
            rand_expBasis = { 64, 128 };
            rand_expInfla = { 2, 8 };
            minmax_lvl = { 1, 50 };
            criticalHit = 10;
            hitRate = 80;
            break;
        case data::CreatureLevel::Baby2:
            rand_attrBasis = { 5, 10 };
            rand_attrInfla = { 4, 8 };
            rand_expBasis = { 64, 128 };
            rand_expInfla = { 2, 8 };
            minmax_lvl = { 1, 80 };
            criticalHit = 10;
            hitRate = 80;
            break;
        case data::CreatureLevel::Child:
            rand_attrBasis = { 8, 15 };
            rand_attrInfla = { 12, 18 };
            rand_expBasis = { 64, 128 };
            rand_expInfla = { 16, 32 };
            minmax_lvl = { 1, 100 };
            criticalHit = 20;
            hitRate = 90;
            break;
        case data::CreatureLevel::Adult:
            rand_attrBasis = { 13, 21 };
            rand_attrInfla = { 16, 25 };
            rand_expBasis = { 128, 128 };
            rand_expInfla = { 128, 256 };
            minmax_lvl = { 1, 100 };
            criticalHit = 30;
            hitRate = 90;
            break;
        case data::CreatureLevel::Perfect:
            rand_attrBasis = { 18, 28 };
            rand_attrInfla = { 23, 32 };
            rand_expBasis = { 128, 256 };
            rand_expInfla = { 128, 256 };
            minmax_lvl = { 1, 128 };
            criticalHit = 30;
            hitRate = 90;
            break;
        case data::CreatureLevel::Ultimate:
            rand_attrBasis = { 25, 32 };
            rand_attrInfla = { 29, 36 };
            rand_expBasis = { 128, 256 };
            rand_expInfla = { 128, 256 };
            minmax_lvl = { 1, 255 };
            criticalHit = 30;
            hitRate = 90;
            break;
        case data::CreatureLevel::Egg:
        case data::CreatureLevel::END:
            rand_attrBasis = { 1, 1 };
            rand_attrInfla = { 1, 1 };
            rand_expBasis = { 1, 1 };
            rand_expInfla = { 1, 1 };
            minmax_lvl = { 1, 1 };
            criticalHit = 0;
            hitRate = 0;
            break;
    }

    switch (state) {
        case DataCreatureEvol::BadMiss:
            std::get<0>(rand_attrBasis) *= util::random(30, 50) / 100.0;
            std::get<1>(rand_attrBasis) *= util::random(30, 50) / 100.0;

            std::get<0>(rand_attrInfla) *= util::random(30, 50) / 100.0;
            std::get<1>(rand_attrInfla) *= util::random(30, 50) / 100.0;

            std::get<0>(rand_expBasis) *= util::random(40, 60) / 100.0;
            std::get<1>(rand_expBasis) *= util::random(50, 60) / 100.0;

            std::get<0>(rand_expInfla) *= util::random(40, 60) / 100.0;
            std::get<1>(rand_expInfla) *= util::random(50, 60) / 100.0;

            criticalHit *= util::random(80, 90) / 100.0;
            hitRate *= util::random(80, 90) / 100.0;

            if (creatureLevel > +data::CreatureLevel::Child) {
                int luck = util::random(0, 30);
                luck -= luck % 10;
                creature_evolCondition.setLuck(luck);

                int disc = util::random(0, 30);
                disc -= luck % 10;
                creature_evolCondition.setDisc(disc);
            }
            break;
        case DataCreatureEvol::Bad:
            std::get<0>(rand_attrBasis) *= util::random(50, 80) / 100.0;
            std::get<1>(rand_attrBasis) *= util::random(50, 80) / 100.0;

            std::get<0>(rand_attrInfla) *= util::random(50, 80) / 100.0;
            std::get<1>(rand_attrInfla) *= util::random(50, 80) / 100.0;

            std::get<0>(rand_expBasis) *= util::random(65, 85) / 100.0;
            std::get<1>(rand_expBasis) *= util::random(65, 85) / 100.0;

            std::get<0>(rand_expInfla) *= util::random(60, 80) / 100.0;
            std::get<1>(rand_expInfla) *= util::random(60, 80) / 100.0;

            criticalHit *= util::random(90, 95) / 100.0;
            hitRate *= util::random(90, 95) / 100.0;

            if (creatureLevel > +data::CreatureLevel::Child) {
                int luck = util::random(40, 60);
                luck -= luck % 10;
                creature_evolCondition.setLuck(luck);

                int disc = util::random(40, 60);
                disc -= luck % 10;
                creature_evolCondition.setDisc(disc);
            }
            break;
        case DataCreatureEvol::Good:
            std::get<0>(rand_attrBasis) *= util::random(105, 110) / 100.0;
            std::get<1>(rand_attrBasis) *= util::random(105, 110) / 100.0;

            std::get<0>(rand_attrInfla) *= util::random(102, 105) / 100.0;
            std::get<1>(rand_attrInfla) *= util::random(102, 105) / 100.0;

            std::get<0>(rand_expBasis) *= util::random(1010, 1020) / 1000.0;
            std::get<1>(rand_expBasis) *= util::random(1010, 1020) / 1000.0;

            std::get<0>(rand_expInfla) *= util::random(1010, 1020) / 1000.0;
            std::get<1>(rand_expInfla) *= util::random(1010, 1020) / 1000.0;

            criticalHit *= util::random(1000, 1010) / 1000.0;

            if (creatureLevel > +data::CreatureLevel::Child) {
                int luck = util::random(90, 100);
                luck -= luck % 10;
                creature_evolCondition.setLuck(luck);

                int disc = util::random(90, 100);
                disc -= luck % 10;
                creature_evolCondition.setDisc(disc);
            }
            break;
        case DataCreatureEvol::Normal:
            if (creatureLevel > +data::CreatureLevel::Child) {
                int luck = util::random(50, 80);
                luck -= luck % 10;
                creature_evolCondition.setLuck(luck);

                int disc = util::random(50, 80);
                disc -= luck % 10;
                creature_evolCondition.setDisc(disc);
            }
            break;
    }

    std::get<0>(rand_attrBasis) = std::max(1, std::get<0>(rand_attrBasis));
    std::get<1>(rand_attrBasis) = std::max(1, std::get<1>(rand_attrBasis));

    std::get<0>(rand_attrInfla) = std::max(1, std::get<0>(rand_attrInfla));
    std::get<1>(rand_attrInfla) = std::max(1, std::get<1>(rand_attrInfla));

    std::get<0>(rand_expBasis) = std::max(1, std::get<0>(rand_expBasis));
    std::get<1>(rand_expBasis) = std::max(1, std::get<1>(rand_expBasis));

    std::get<0>(rand_expInfla) = std::max(1, std::get<0>(rand_expInfla));
    std::get<1>(rand_expInfla) = std::max(1, std::get<1>(rand_expInfla));

    criticalHit = std::max(1, criticalHit);
    hitRate = std::max(1, hitRate);

    creature.setEvolCondition(creature_evolCondition);

    makeDataCreature(creature, name, cls, rand_attrBasis, rand_attrInfla,
                     rand_expBasis, rand_expInfla, creatureRhythm,
                     creatureLevel, type, elements, minmax_lvl, criticalHit,
                     hitRate, evol_weight, bodysize, gender);
}

void DataCreatureMaker::calcStatuses(data::Creature& creature) {
    creature.clearStatusResist();
    for (const auto& status : this->datamanager_.getCreatureBattlerStatuses()) {
        if(status){
            creature.setStatusResist(*status,
                                     data::Resist::Normal);
        }
    }
}

void DataCreatureMaker::calcElements(data::Creature& creature,
                                     const std::vector<std::string>& elements) {
    creature.clearElements();
    for (std::string elementname : elements) {
        auto element = this->datamanager_.findElement(elementname);

        if (element) {
            creature.addElement(*element);
        } else {
            std::cerr << "calcElements: " << elementname << " "
                      << " Not Found"
                      << '\n';
        }

    }

    std::unordered_map<std::string, int> count_elements_value;
    std::unordered_map<std::string, int> elements_value;
    for (const auto& element : this->datamanager_.getElements()) {
        if(element){
            std::string element_name = element->getName();
            elements_value[element_name] = 100;
            count_elements_value[element_name] = 1;
        }
    }


    for (const auto& element : this->datamanager_.getElements()) {
        if(element){
            std::string element_name = element->getName();

            for (std::string elementname : elements) {
                if (element_name == elementname) {
                    elements_value[element_name] += 50;
                    count_elements_value[element_name]++;
                } else {
                    if (this->resists_.find(element_name) == std::end(this->resists_)) {
                        std::cerr << "calcElements: Element in resists_ not found"
                                << '\n';
                        continue;
                    }

                    const std::vector<std::string>& pluses = std::get<0>(this->resists_.at(element_name));
                    for (std::string plus_element : pluses) {
                        if (elementname == plus_element) {
                            elements_value[element_name] += 150;
                        } else {
                            elements_value[element_name] += 100;
                        }
                        count_elements_value[element_name]++;
                    }

                    const std::vector<std::string>& minuses = std::get<1>(this->resists_.at(element_name));
                    for (std::string minus_element : minuses) {
                        if (elementname == minus_element) {
                            elements_value[element_name] += 50;
                        } else {
                            elements_value[element_name] += 100;
                        }
                        count_elements_value[element_name]++;
                    }
                }
            }
        }
    }

    for (auto& element_value : elements_value) {
        if(count_elements_value[element_value.first] != 0){
            element_value.second /= count_elements_value[element_value.first];
        } else {
            element_value.second = 100;
        }
    }

    creature.clearElementResist();
    for (const auto& element_value : elements_value) {
        auto element = this->datamanager_.findElement(element_value.first);

        if(element){
            if (element_value.second >= 200) {
                creature.setElementResist(*element,
                                        data::Resist::MoreSensitivity);
            } else if (element_value.second >= 150) {
                creature.setElementResist(*element,
                                        data::Resist::Sensitivity);
            } else if (element_value.second >= 100) {
                creature.setElementResist(*element,
                                        data::Resist::Normal);
            } else if (element_value.second >= 50) {
                creature.setElementResist(*element,
                                        data::Resist::Resistance);
            } else if (element_value.second > 0) {
                creature.setElementResist(*element,
                                        data::Resist::MoreResistance);
            } else if (element_value.second == 0) {
                creature.setElementResist(*element,
                                        data::Resist::Immune);
            } else if (element_value.second < 0) {
                creature.setElementResist(*element,
                                        data::Resist::Heal);
            } else {
                creature.setElementResist(*element,
                                        data::Resist::Normal);
            }
        }
    }
}


} // namespace datamaker