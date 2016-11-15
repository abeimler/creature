#include "InitData.h"

using namespace datamaker;

void InitData::makeCreature2() {
    makeDataCreature("DigiTama02", "Digitama",
                     datamaker::DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Egg, 5, 0.3f);

    makeDataCreature("Punimon", "Slime", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Baby, 5, 0.2f);

    makeDataCreature("Tsunomon", "Lesser", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Baby2, 10, 1.0f);

    makeDataCreature(
        "Gabumon", "Reptile", DataCreatureEvol::Normal,
        DataCreatureClass::Starter, {"Metal Empire", "Nature Spirits"},
        DataCreatureAttribute::Vaccine, data::CreatureLevel::Child, 20, 1.2f);

    makeDataCreature(
        "Elecmon", "Mammal", DataCreatureEvol::Normal,
        DataCreatureClass::Normal, {"Deep Savers", "Nature Spirits"},
        DataCreatureAttribute::Data, data::CreatureLevel::Child, 20, 1.0f);



    makeDataCreature("Kabuterimon", "Insect", DataCreatureEvol::Normal,
                     DataCreatureClass::Knight,
                     {"Jungle Troopers", "Nature Spirits", "Wind Guardians"},
                     DataCreatureAttribute::Vaccine, data::CreatureLevel::Adult,
                     30, 10.0f);

    makeDataCreature(
        "Garurumon", "Beast", DataCreatureEvol::Good, DataCreatureClass::Hunter,
        {"Metal Empire", "Nature Spirits", "Nightmare Soldiers"},
        DataCreatureAttribute::Data, data::CreatureLevel::Adult, 20, 6.0f);

    makeDataCreature(
        "Garurumon (Black)", "Beast", DataCreatureEvol::Good,
        DataCreatureClass::Hunter, {"Nature Spirits", "Nightmare Soldiers"},
        DataCreatureAttribute::Virus, data::CreatureLevel::Adult, 20, 6.0f);

    makeDataCreature(
        "Angemon", "Angel", DataCreatureEvol::Bad, DataCreatureClass::Wizard,
        {"Virus Busters", "Wind Guardians"}, DataCreatureAttribute::Vaccine,
        data::CreatureLevel::Adult, 20, 2.5f);



    makeDataCreature("Yukidarumon", "Icy Snow", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal,
                     {"Nature Spirits", "Nightmare Soldiers", "Deep Savers"},
                     DataCreatureAttribute::Vaccine, data::CreatureLevel::Adult,
                     30, 2.0f);

    makeDataCreature(
        "Birdramon", "Giant Bird", DataCreatureEvol::Normal,
        DataCreatureClass::Knight, {"Nature Spirits", "Wind Guardians"},
        DataCreatureAttribute::Data, data::CreatureLevel::Adult, 30, 6.0f);

    makeDataCreature("Whamon", "Aquatic", DataCreatureEvol::Normal,
                     DataCreatureClass::Mage, {"Deep Savers"},
                     DataCreatureAttribute::Vaccine, data::CreatureLevel::Adult,
                     50, 30.0f);



    makeDataCreature("Vegimon", "Plant", DataCreatureEvol::BadMiss,
                     DataCreatureClass::Healer, {"Nature Spirits"},
                     DataCreatureAttribute::Virus, data::CreatureLevel::Adult,
                     10, 1.0f);


    makeDataCreature(
        "SkullGreymon", "Skeleton", DataCreatureEvol::Bad,
        DataCreatureClass::Warrior, {"Dragons Roar", "Nightmare Soldiers"},
        DataCreatureAttribute::Virus, data::CreatureLevel::Perfect, 20, 15.0f);



    makeDataCreature("Vademon", "Alien", DataCreatureEvol::Bad,
                     DataCreatureClass::Mage, {"Dark Area"},
                     DataCreatureAttribute::Virus, data::CreatureLevel::Perfect,
                     20, 1.6f);



    makeDataCreature(
        "MetalMamemon", "Cyborg", DataCreatureEvol::Normal,
        DataCreatureClass::Knight, {"Metal Empire", "Virus Busters"},
        DataCreatureAttribute::Data, data::CreatureLevel::Perfect, 5, 0.8f);

    makeDataCreature("WereGarurumon", "Beast Man", DataCreatureEvol::Good,
                     DataCreatureClass::Hunter,
                     {"Nature Spirits", "Metal Empire", "Nightmare Soldiers"},
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Perfect, 16, 1.8f);

    makeDataCreature(
        "WereGarurumon (Black)", "Beast Man", DataCreatureEvol::Good,
        DataCreatureClass::Hunter, {"Nature Spirits", "Nightmare Soldiers"},
        DataCreatureAttribute::Virus, data::CreatureLevel::Perfect, 16, 1.8f);



    makeDataCreature("MetalGarurumon", "Cyborg", DataCreatureEvol::Normal,
                     DataCreatureClass::Hunter, {"Metal Empire"},
                     DataCreatureAttribute::Data, data::CreatureLevel::Ultimate,
                     28, 2.2f);

    makeDataCreature("MetalGarurumon (Black)", "Cyborg", DataCreatureEvol::Good,
                     DataCreatureClass::Hunter, {"Metal Empire"},
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Ultimate, 28, 2.2f);
}

void InitData::updateCreature2() {
    updateEvolution("DigiTama02", {"Punimon"});

    updateEvolution("Punimon", {"Tsunomon"});

    updateEvolution("Tsunomon", {"Gabumon", "Elecmon"});

    updateEvolution("Gabumon",
                    {"Garurumon", "Kabuterimon", "Yukidarumon", "Angemon"},
                    {"Vegimon"});

    updateEvolution("Elecmon",
                    {"Birdramon", "Whamon", "Yukidarumon", "Angemon"},
                    {"Vegimon"});

    updateEvolution("Garurumon",
                    {"WereGarurumon", "WereGarurumon (Black)", "MetalMamemon"});

    updateEvolution("Kabuterimon", {"SkullGreymon"});

    updateEvolution("Yukidarumon", {"MetalMamemon"});

    updateEvolution("Angemon", {"SkullGreymon"});

    updateEvolution("Whamon", {"MetalMamemon"});

    updateEvolution("Birdramon", {"SkullGreymon"});

    updateEvolution("Vegimon", {"Vademon"});

    updateEvolution("MetalMamemon", {});

    updateEvolution("Vademon", {});

    // updateEvolution("SkullGreymon", {});

    updateEvolution("WereGarurumon", {"MetalGarurumon"});

    updateEvolution("WereGarurumon (Black)", {"MetalGarurumon (Black)"});

    updateEvolution("MetalGarurumon", {});

    updateEvolution("MetalGarurumon (Black)", {});
}
