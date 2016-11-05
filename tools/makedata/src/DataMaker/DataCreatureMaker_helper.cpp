#include "DataMaker/DataCreatureMaker.h"

void DataCreatureMaker::reloadDataOnce() {
    if (!this->datamanager_.getCreatures().empty())
        return;

    this->reloadData();
}

void DataCreatureMaker::reloadData() {
    // TODO load data from file
}

void DataCreatureMaker::saveCreature(data::Creature& data_creature) {
    std::cout << "save creature data " << data_creature.getName() << '\n';

    this->datamanager_.saveCreature(data_creature);
}

void DataCreatureMaker::updateEvolution(
    std::string name, 
    const std::vector<std::string>& nexts,
    const std::vector<std::string>& misses) {
    std::vector<std::string> nexts_names;
    std::vector<std::string> misses_names;

    std::cout << "update creature evol: " << name << "... ";

    for (auto nextname : nexts) {
        auto find_creature = this->datamanager_.findCreature(nextname);
        if (find_creature) {
            nexts_names.push_back(find_creature->getName());
        } else {
            std::cout << nextname << " not found" << '\n';
        }
    }

    for (auto missname : misses) {
        auto find_creature = this->datamanager_.findCreature(missname);
        if (find_creature) {
            misses_names.push_back(find_creature->getName());
        } else {
            std::cout << missname << " not found" << '\n';
        }
    }

    auto find_creature = this->datamanager_.findCreature(name);
    if (find_creature) {
        updateEvolution(*find_creature, nexts_names, misses_names);
    } else {
        std::cout << name << " not found" << '\n';
    }
}

void DataCreatureMaker::updateEvolution(std::string name,
                                        const std::vector<std::string>& nexts) {
    std::vector<std::string> nexts_names;

    std::cout << "update creature evol: " << name << "... ";

    for (auto nextname : nexts) {
        auto find_creature = this->datamanager_.findCreature(nextname);
        if (find_creature) {
            nexts_names.push_back(find_creature->getName());
        } else {
            std::cout << nextname << " not found" << '\n';
        }
    }

    auto find_creature = this->datamanager_.findCreature(name);
    if (find_creature) {
        updateEvolution(*find_creature, nexts_names);
    } else {
        std::cout << name << " not found" << '\n';
    }
}

void DataCreatureMaker::updateEvolutionCond(
    data::Creature& data_creature,
    const std::vector<std::string>& prevs) {

    data::EvolutionCondition evolCondition =
        data_creature.getEvolCondition();
    data::CreatureLevel creatureLevel =
        data_creature.getCreatureLevel();

    int lvl = getLeveltoEvol(creatureLevel);

    if (creatureLevel >= +data::CreatureLevel::Baby2) {
        for (auto index : earr::Enum<data::Attribute>()) {
            std::vector<int> attrs =
                this->creaturebattlercreator_.genAttrs<int>(data_creature,
                                                            index);

            int min_attr = evolCondition.getAttr(index);
            if (creatureLevel < +data::CreatureLevel::Adult) {
                if (lvl > 1) {
                    size_t lvl_size = static_cast<size_t>(lvl);
                    min_attr = std::min<int>(min_attr, attrs[lvl_size - 1]);
                }
            }

            for (std::string prev_name : prevs) {
                auto creature_prev = this->datamanager_.findCreature(prev_name);

                if (creature_prev) {
                    std::vector<int> prevs_attrs =
                    this->creaturebattlercreator_.genAttrs<int>(*creature_prev,
                                                                index);

                    if(prevs_attrs.size() > 1){
                        min_attr = std::min<int>(min_attr, prevs_attrs[prevs_attrs.size() - 2]);
                    } else {
                        min_attr = 0;
                    }
                } else {
                    std::cerr << "updateEvolutionCond: prev creature "
                              << prev_name << " not found"
                              << '\n';
                }
            }

            evolCondition.setAttr(index, min_attr);
        }
    }

    data_creature.setEvolCondition(evolCondition);

    this->updateCreature(data_creature);
}



void DataCreatureMaker::updateEvolutionNextPrev(
    data::Creature& data_creature,
    const std::vector<std::string>& nexts) {

    for (std::string next_name : nexts) {
        auto creature_next = this->datamanager_.findCreature(next_name);

        if (creature_next) {
            auto prev_creatures = creature_next->getPrevCreatures();
            auto prev_creatures_it = std::find(std::begin(prev_creatures), std::end(prev_creatures), next_name);
            if(prev_creatures_it == std::end(prev_creatures)){
                creature_next->addPrevCreature(data_creature);
            }

            this->updateCreature(*creature_next);
        } else {
            std::cerr << "updateEvolutionNextPrev: next creature " << next_name
                      << " not found" << '\n';
        }

    }

    this->updateCreature(data_creature);
}

void DataCreatureMaker::updateEvolutionMissPrev(
    data::Creature& data_creature,
    const std::vector<std::string>& misses) {
        
    for (std::string miss_name : misses) {
        auto creature_miss = this->datamanager_.findCreature(miss_name);

        if (creature_miss) {
            auto prev_creatures = creature_miss->getPrevCreatures();
            auto prev_creatures_it = std::find(std::begin(prev_creatures), std::end(prev_creatures), miss_name);
            if(prev_creatures_it == std::end(prev_creatures)){
                creature_miss->addPrevCreature(data_creature);
            }

            this->updateCreature(*creature_miss);
        } else {
            std::cerr << "updateEvolutionMissPrev: miss creature " << miss_name
                      << " not found" << '\n';
        }

    }

    this->updateCreature(data_creature);
}

void DataCreatureMaker::updateEvolution(
    data::Creature& data_creature,
    const std::vector<std::string>& nexts) {
    std::cout << "update creature evol: " << data_creature.getName() << " , ";

    for (std::string next_name : nexts) {
        auto creature_next = this->datamanager_.findCreature(next_name);

        if (creature_next) {
            auto next_creatures = data_creature.getNextCreatures();
            auto next_creatures_it = std::find(std::begin(next_creatures), std::end(next_creatures), next_name);
            if(next_creatures_it == std::end(next_creatures)){
                data_creature.addNextCreature(*creature_next);
            }

            this->updateCreature(data_creature);
        } else {
            std::cerr << "updateEvolution: next creature " << next_name
                      << " not found" << '\n';
        }
    }

    updateEvolutionNextPrev(data_creature, nexts);

    std::cout << '\n';
}

void DataCreatureMaker::updateEvolution(
    data::Creature& data_creature,
    const std::vector<std::string>& nexts, 
    const std::vector<std::string>& misses) {

    updateEvolution(data_creature, nexts);


    for (std::string miss_name : misses) {
        auto creature_miss = this->datamanager_.findCreature(miss_name);

        if (creature_miss) {
            auto miss_creatures = data_creature.getMissCreatures();
            auto miss_creatures_it = std::find(std::begin(miss_creatures), std::end(miss_creatures), miss_name);
            if(miss_creatures_it == std::end(miss_creatures)){
                data_creature.addMissCreature(*creature_miss);
            }

            this->updateCreature(data_creature);
        } else {
            std::cerr << "updateEvolution: miss creature " << miss_name
                      << " not found" << '\n';
        }
    }

    updateEvolutionMissPrev(data_creature, misses);

    std::cout << '\n';
}

void DataCreatureMaker::updateCreature(data::Creature& data_creature) {
    
    std::cout << "update creature: " << data_creature.getName() << " ";

    this->datamanager_.saveCreature(data_creature);

    std::cout << '\n';
}

void DataCreatureMaker::makeStarter() {
    for (const auto& creature : this->datamanager_.getCreatures()) {
        if (creature && creature->getCreatureLevel() == +data::CreatureLevel::Egg) {
            std::cout << "creature starter: " << creature->getName() << " ";

            this->datamanager_.saveCreatureStarter(*creature);

            std::cout << '\n';
        }
    }
}
