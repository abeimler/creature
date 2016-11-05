#include "InitData.h"

using namespace datamaker;

void InitData::makeDataCreature(
    std::string name, std::string type, DataCreatureEvol state,
    DataCreatureClass cls, const std::vector<std::string>& elements,
    data::CreatureCircadianRhythm creatureRhythm,
    data::CreatureLevel creatureLevel, float evol_weight, float bodysize,
    DataCreatureGender gender) {

    this->maker_.makeDataCreature(name, type, state, cls, elements,
                                   creatureRhythm, creatureLevel, evol_weight,
                                   bodysize, gender);
}


void InitData::makeDataCreature(std::string name, std::string type,
                                DataCreatureEvol state, DataCreatureClass cls,
                                const std::vector<std::string>& elements,
                                DataCreatureAttribute dataCreatureAttribute,
                                data::CreatureLevel creatureLevel,
                                float evol_weight, float bodysize,
                                DataCreatureGender gender) {
    /*
     * None
     * Crepuscular  during twilight (i.e., dawn and dusk).
     * Diurnal      during the day and sleeping, or other inactivity, at night.
     * Nocturnal    activity during the night and sleeping during the day.
     * Variable
     * Unknown
     */

    data::CreatureCircadianRhythm creatureRhythm =
        data::CreatureCircadianRhythm::None;
    switch (dataCreatureAttribute) {
        case DataCreatureAttribute::None:
            creatureRhythm = data::CreatureCircadianRhythm::None;
            break;
        case DataCreatureAttribute::Vaccine:
            creatureRhythm = data::CreatureCircadianRhythm::Diurnal;
            break;
        case DataCreatureAttribute::Data:
            creatureRhythm = data::CreatureCircadianRhythm::Crepuscular;
            break;
        case DataCreatureAttribute::Virus:
            creatureRhythm = data::CreatureCircadianRhythm::Nocturnal;
            break;
        case DataCreatureAttribute::Free:
            creatureRhythm = data::CreatureCircadianRhythm::Variable;
            break;
        case DataCreatureAttribute::Variable:
            creatureRhythm = data::CreatureCircadianRhythm::Variable;
            break;
        case DataCreatureAttribute::Unknown:
            creatureRhythm = data::CreatureCircadianRhythm::Unknown;
            break;
    }


    this->makeDataCreature(name, type, state, cls, elements, creatureRhythm,
                           creatureLevel, evol_weight, bodysize, gender);
}


void InitData::updateEvolution(std::string name,
                               const std::vector<std::string>& nexts) {
    this->maker_.updateEvolution(name, nexts);
}
void InitData::updateEvolution(std::string name,
                               const std::vector<std::string>& nexts,
                               const std::vector<std::string>& misses) {
    this->maker_.updateEvolution(name, nexts, misses);
}



void InitData::initElements(){
    this->elements_ = {
        "Nature Spirits",
        "Deep Savers",
        "Nightmare Soldiers",
        "Wind Guardians",
        "Metal Empire",
        "Unknown",
        "Dark Area",
        "Virus Busters",
        "Dragons Roar",
        "Jungle Troopers",
        "X-Antibody"
    };



    /**
    Nature Spirits      : Generic monsters and beasts. Also represents
    grasslands and canyons.
    Deep Savers	        : Aquatic or ice-related Creature. Can represent the
    ocean or arctic.
    Nightmare Soldiers  : Darkness or spirit based Creature, or Creature based
    on traditional "Halloween" monsters like vampires, werewolves, or Japanese
    youkai and demons. Can represent haunted or cursed areas.
    Wind Guardians      : Flying, air, or plant based Creature. Can represent
    forests and the sky.
    Metal Empire        : Machine, cyborg, or other mechanical Creature. Can
    represent cities and factories.
    Unknown             : Mutant, unusual, or strange Creature. Can represent
    junkyards and other strange places.
    Dark Area           : Villanous, demonic, terrifying, evil Creature. Can
    represent the Dark Area of the Digital World.
    Virus Busters       : Heroic or angelic Creature, often includes main
    characters from the anime or manga. Can represent the sky or heavens.
    Dragon's Roar       : Draconic Creature.
    Jungle Troopers     : Plant or Insect based Creature.

    NS: +(), -()
    DS: +(DR), -(JT)
    NS: +(VB), -(ME)
    WG: +(JT), -(ME)
    ME: +(WG), -(DR)
    UK: +(), -()
    DA: +(NS), -(ME)
    VB: +(DA), -(ME)
    DR: +(JT), -(DS)
    JT: +(ME), -(DR)
    */

    this->elements_resists_.clear();

    this->elements_resists_["Nature Spirits"] = { {}, {} };
    this->elements_resists_["Deep Savers"] = {
        { "Dragons Roar" }, { "Jungle Troopers" }
    };
    this->elements_resists_["Nightmare Soldiers"] = {
        { "Virus Busters" }, { "Metal Empire", "Nightmare Soldiers" }
    };
    this->elements_resists_["Wind Guardians"] = {
        { "Jungle Troopers" }, { "Metal Empire" }
    };
    this->elements_resists_["Metal Empire"] = {
        { "Wind Guardians", "Deep Savers" }, { "Dragons Roar" }
    };
    this->elements_resists_["Unknown"] = { {}, {} };
    this->elements_resists_["Dark Area"] = {
        { "Nightmare Soldiers" }, { "Metal Empire", "Virus Busters" }
    };
    this->elements_resists_["Virus Busters"] = {
        { "Dark Area" }, { "Metal Empire", "Nightmare Soldiers" }
    };
    this->elements_resists_["Dragons Roar"] = {
        { "Jungle Troopers" }, { "Deep Savers" }
    };
    this->elements_resists_["Jungle Troopers"] = {
        { "Metal Empire" }, { "Wind Guardians", "Dragons Roar" }
    };
    this->elements_resists_["X-Antibody"] = {
        { "Nature Spirits", "Deep Savers", "Nightmare Soldiers",
          "Wind Guardians", "Metal Empire", "Dark Area", "Virus Busters",
          "Dragons Roar", "Jungle Troopers" },
        {}
    };
}

void InitData::initTypes() {

    this->types_ = {

        { "Digitama", { 
            "Digitama" 
        }},

        { "Little", {
            "Slime", "Lesser", "Bulb", "Slime Angle", "Slime Bird", "Slime Devil", "Slime Dragon"
        }},

        { "Alien", { 
            "Alien" 
        }},

        { "Amphibian", { 
            "Amphibian" 
        }},

        { "Ancient", {
            "Ancient Aquatic Beast Man", 
            "Ancient Aquatic Beast Man", 
            "Ancient Beast", 
            "Ancient Bird", 
            "Ancient Crustacean", 
            "Ancient Dragon Man", 
            "Ancient Fish",
            "Ancient Holy Knight",
            "Ancient Insect", 
            "Ancient Mutant",
            "Ancient Mythical Beast",
            "Ancient Ore",
            "Ancient Plant",
            "Rare Animal"
        }},

        { "Holy", {
            "Angel", 
            "Archangel", 
            "Dominion", 
            "Seraph", 
            "Viture", 
            "Ophan"
        }},

        { "Unholy", {
            "Fallen Angel", 
            "Artificial Fallen Angel", 
            "Devil"
        }},

        { "Reptile", {
            "Reptile", 
            "Dinosaur", 
            "Ankylosaur",
            "Ceratopsian",
            "Plesiosaur",
            "Pterosaur",
            "Stegosaur"
        }},

        { "Mammal", { 
            "Mammal" 
        }},

        { "Aquatic", {
            "Aquatic", 
            "Aquatic Beast Man", 
            "Aquatic Mammal",
            "Crustacean",
            "Marine Animal",
            "Marine Man",
            "Tropical Fish"
        }},

        { "Avatar", { 
            "Avatar" 
        }},
    };

    /*




    makeType("Dragon", "Dragon");
    makeType("Baby Dragon", "Dragon");
    makeType("Dragon Man", "Dragon");
    makeType("Dragon Warrior", "Dragon");
    makeType("Beast Dragon", "Dragon");
    makeType("Dark Dragon", "Dragon");
    makeType("Evil Dragon", "Dragon");
    makeType("Holy Dragon", "Dragon");
    makeType("Light Dragon", "Dragon");
    makeType("Mythical Dragon", "Dragon");
    makeType("Ocean Dragon", "Dragon");
    makeType("Sky Dragon", "Dragon");

    makeType("Beast", "Beast");
    makeType("Mythical Beast", "Beast");
    makeType("Beast Knight", "Beast");
    makeType("Beast Man", "Beast");
    makeType("God Beast", "Beast");
    makeType("Holy Beast", "Beast");
    makeType("Synthetic Beast", "Beast");

    makeType("Bewitching Beast", "Bewitching");
    makeType("Bewitching Bird", "Bewitching");

    makeType("Bird", "Bird");
    makeType("Bird Man", "Bird");
    makeType("Chick", "Bird");
    makeType("Giant Bird", "Bird");
    makeType("Holy Bird", "Bird");

    makeType("Machine", "Machine");
    makeType("Cyborg", "Machine");
    makeType("Machine Dragon", "Machine");
    makeType("Mine", "Machine");

    makeType("Dark Knight", "Knight");
    makeType("Holy Knight", "Knight");
    makeType("Magic Warrior", "Knight");
    makeType("Warrior", "Knight");

    makeType("Demon Beast", "Demon");
    makeType("Demon Dragon", "Demon");
    makeType("Demon God", "Demon");
    makeType("Demon Lord", "Demon");
    makeType("Demon Man", "Demon");

    makeType("Fairy", "Fairy");
    makeType("Spirit", "Fairy");

    makeType("Oni", "Monster");
    makeType("Mutant", "Monster");

    makeType("Rock", "Rock");
    makeType("Mineral", "Rock");
    makeType("Ore", "Rock");

    makeType("Flame", "Flame");
    makeType("Flame Dragon", "Flame");
    makeType("Smoke", "Flame");

    makeType("Hybrid", "Hybrid");
    makeType("Enhancement", "Hybrid");
    makeType("Composite", "Hybrid");
    makeType("Unique", "Hybrid");

    makeType("Icy Snow", "Ice");

    makeType("Insect", "Insect");
    makeType("Larva", "Insect");
    makeType("Parasite", "Insect");

    makeType("Insectivorous Plant", "Plant");

    makeType("Mollusk", "Mollusk");

    makeType("Plant", "Plant");
    makeType("Seed", "Plant");

    makeType("Toy", "Toy");
    makeType("Puppet", "Toy");

    makeType("Undead", "Undead");
    makeType("Skeleton", "Undead");
    makeType("Ghost", "Undead");

    makeType("Unknown", "Unknown");
    makeType("Perfect", "Unknown");
    makeType("9000", "Unknown");
    makeType("Unanalyzable", "Unknown");
    makeType("No Data", "Unknown");
    */
}