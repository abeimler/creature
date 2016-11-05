#include "InitData.h"

using namespace datamaker;

void InitData::makeCreature1() {
    makeDataCreature("DigiTama01", "Digitama", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Egg, 5, 0.3f);

    makeDataCreature("Botamon", "Slime", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Baby, 5, 0.2f);

    makeDataCreature("Koromon", "Lesser", DataCreatureEvol::Normal,
                     DataCreatureClass::Normal, {}, DataCreatureAttribute::None,
                     data::CreatureLevel::Baby2, 10, 0.9f);



    makeDataCreature(
        "Agumon", "Reptile", DataCreatureEvol::Good, DataCreatureClass::Starter,
        { "Metal Empire", "Nature Spirits" }, DataCreatureAttribute::Vaccine,
        data::CreatureLevel::Child, 15, 1.2f);

    makeDataCreature("Betamon", "Amphibian", DataCreatureEvol::Normal,
                     DataCreatureClass::Hunter, { "Nature Spirits" },
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Child, 20, 1.0f);



    makeDataCreature("Greymon", "Dinosaur", DataCreatureEvol::Good,
                     DataCreatureClass::Warrior,
                     { "Metal Empire", "Nature Spirits", "Dragons Roar" },
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Adult, 40, 12.0f);

    makeDataCreature("Tyranomon", "Dinosaur", DataCreatureEvol::Normal,
                     DataCreatureClass::Warrior,
                     { "Metal Empire", "Nature Spirits", "Nightmare Soldiers" },
                     DataCreatureAttribute::Data,
                     data::CreatureLevel::Adult, 20, 10.8f);

    makeDataCreature("Devimon", "Fallen Angel", DataCreatureEvol::Bad,
                     DataCreatureClass::Mage, { "Nightmare Soldiers" },
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Adult, 15, 2.5f);



    makeDataCreature(
        "Meramon", "Flame", DataCreatureEvol::Normal, DataCreatureClass::Knight,
        { "Nature Spirits", "Nightmare Soldiers" }, DataCreatureAttribute::Data,
        data::CreatureLevel::Adult, 30, 1.9f);

    makeDataCreature("Airdramon", "Mythical Beast", DataCreatureEvol::Bad,
                     DataCreatureClass::Thief,
                     { "Nature Spirits", "Wind Guardians" },
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Adult, 20, 8.f);

    makeDataCreature("Seadramon", "Aquatic", DataCreatureEvol::Good,
                     DataCreatureClass::WarriorThief, { "Deep Savers" },
                     DataCreatureAttribute::Data,
                     data::CreatureLevel::Adult, 20, 6.0f);



    makeDataCreature("Numemon", "Mollusk", DataCreatureEvol::BadMiss,
                     DataCreatureClass::Normal,
                     { "Metal Empire", "Nightmare Soldiers" },
                     DataCreatureAttribute::Data,
                     data::CreatureLevel::Adult, 10, 0.8f);



    makeDataCreature("MetalGreymon", "Cyborg", DataCreatureEvol::Good,
                     DataCreatureClass::Warrior,
                     { "Dragons Roar", "Metal Empire", "Nature Spirits" },
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Perfect, 40, 14.0f);

    makeDataCreature("MetalGreymon (Virus)", "Cyborg", DataCreatureEvol::Good,
                     DataCreatureClass::Warrior, { "Dragons Roar" },
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Perfect, 40, 14.0f);


    makeDataCreature("Mamemon", "Mutant", DataCreatureEvol::Normal,
                     DataCreatureClass::WarriorThief,
                     { "Metal Empire", "Virus Busters" },
                     DataCreatureAttribute::Data,
                     data::CreatureLevel::Perfect, 5, 0.8f);



    makeDataCreature("Monzaemon", "Puppet", DataCreatureEvol::Bad,
                     DataCreatureClass::Healer, { "Metal Empire" },
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Perfect, 40, 3.0f);


    makeDataCreature("SkullGreymon", "Skeleton", DataCreatureEvol::Bad,
                     DataCreatureClass::Warrior,
                     { "Dragons Roar", "Nightmare Soldiers" },
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Perfect, 20, 15.0f);



    makeDataCreature("Wargreymon", "Dragon Man", DataCreatureEvol::Good,
                     DataCreatureClass::Warrior,
                     { "Dragons Roar", "Metal Empire", "Virus Busters" },
                     DataCreatureAttribute::Vaccine,
                     data::CreatureLevel::Ultimate, 20, 2.0f);

    makeDataCreature("BlackWargreymon", "Dragon Man", DataCreatureEvol::Good,
                     DataCreatureClass::Warrior,
                     { "Dragons Roar", "Metal Empire" },
                     DataCreatureAttribute::Virus,
                     data::CreatureLevel::Ultimate, 20, 2.0f);
}



void InitData::updateCreature1() {
    updateEvolution("DigiTama01", { "Botamon" });

    updateEvolution("Botamon", { "Koromon" });

    updateEvolution("Koromon", { "Agumon", "Betamon" });

    updateEvolution("Agumon", { "Greymon", "Tyranomon", "Meramon", "Devimon" },
                    { "Numemon" });

    updateEvolution("Betamon",
                    { "Seadramon", "Airdramon", "Meramon", "Devimon" },
                    { "Numemon" });

    updateEvolution("Greymon", { "MetalGreymon", "MetalGreymon (Virus)" },
                    { "SkullGreymon" });

    updateEvolution("Tyranomon", { "Mamemon" });

    updateEvolution("Meramon", { "Mamemon" });

    updateEvolution("Devimon", { "MetalGreymon (Virus)" });

    updateEvolution("Airdramon", { "MetalGreymon (Virus)" });

    updateEvolution("Seadramon", { "Mamemon" });

    updateEvolution("Numemon", { "Monzaemon" });

    updateEvolution("Mamemon", {});

    updateEvolution("Monzaemon", {});

    updateEvolution("MetalGreymon", { "Wargreymon" }, { "SkullGreymon" });

    updateEvolution("MetalGreymon (Virus)", { "BlackWargreymon" },
                    { "SkullGreymon" });

    updateEvolution("SkullGreymon", {});

    updateEvolution("Wargreymon", {});

    updateEvolution("BlackWargreymon", {});
}


