#include "DataMaker/DataCreatureMaker.h"


void DataCreatureMaker::makeRootType(std::string name) {
    std::cout << "make root type: " << name << " , ";

    auto find_roottype = this->datamanager_.findCreatureRootType(name);
    if(!find_roottype){
        data::CreatureRootType data;
        data.setName(name);
        this->datamanager_.saveCreatureRootType(data);
    }
    
    std::cout << '\n';
}

void DataCreatureMaker::makeType(std::string name, std::string root_name) {
    std::cout << "make type: " << name << "(" << root_name << ")"
              << " , ";

    makeRootType(root_name);

    auto find_roottype = this->datamanager_.findCreatureRootType(name);
    if(!find_roottype){
        if(find_roottype->isExistCreatureType(name)){
            data::CreatureType data;
            data.setName(name);
            find_roottype->addCreatureType(data);
        }

        this->datamanager_.saveCreatureRootType(*find_roottype);
    }

    std::cout << '\n';
}

void DataCreatureMaker::makeTypes() {
    makeType("Digitama", "Digitama");
    makeType("Slime", "Little");
    makeType("Lesser", "Little");
    makeType("Bulb", "Little");
    makeType("Slime Angle", "Little");
    makeType("Slime Bird", "Little");
    makeType("Slime Devil", "Little");
    makeType("Slime Dragon", "Little");

    makeType("Alien", "Alien");
    makeType("Amphibian", "Amphibian");

    makeType("Ancient", "Ancient");
    makeType("Ancient Aquatic Beast Man", "Ancient");
    makeType("Ancient Beast", "Ancient");
    makeType("Ancient Bird", "Ancient");
    makeType("Ancient Bird Man", "Ancient");
    makeType("Ancient Crustacean", "Ancient");
    makeType("Ancient Dragon", "Ancient");
    makeType("Ancient Dragon Man", "Ancient");
    makeType("Ancient Fish", "Ancient");
    makeType("Ancient Holy Knight", "Ancient");
    makeType("Ancient Insect", "Ancient");
    makeType("Ancient Mutant", "Ancient");
    makeType("Ancient Mythical Beast", "Ancient");
    makeType("Ancient Ore", "Ancient");
    makeType("Ancient Plant", "Ancient");
    makeType("Rare Animal", "Ancient");

    makeType("Angel", "Holy");
    makeType("Archangel", "Holy");
    makeType("Dominion", "Holy");
    makeType("Seraph", "Holy");
    makeType("Viture", "Holy");
    makeType("Ophan", "Holy");
    makeType("Monk", "Holy");

    makeType("Fallen Angel", "Unholy");
    makeType("Artificial Fallen Angel", "Unholy");
    makeType("Devil", "Unholy");

    makeType("Reptile", "Reptile");
    makeType("Dinosaur", "Reptile");
    makeType("Ankylosaur", "Reptile");
    makeType("Ceratopsian", "Reptile");
    makeType("Plesiosaur", "Reptile");
    makeType("Pterosaur", "Reptile");
    makeType("Stegosaur", "Reptile");

    makeType("Mammal", "Mammal");

    makeType("Aquatic", "Aquatic");
    makeType("Aquatic Beast Man", "Aquatic");
    makeType("Aquatic Mammal", "Aquatic");
    makeType("Crustacean", "Aquatic");
    makeType("Marine Animal", "Aquatic");
    makeType("Marine Man", "Aquatic");
    makeType("Tropical Fish", "Aquatic");

    makeType("Avatar", "Avatar");

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
}
