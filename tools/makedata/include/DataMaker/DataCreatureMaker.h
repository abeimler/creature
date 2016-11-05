#ifndef DATACREATUREMAKER_H_
#define DATACREATUREMAKER_H_

#include <tuple>

#include "Entity/Data/DataManager.h"

#include "Entity/Game/CreatureBattlerCreator.h"
#include "Entity/Game/CreatureCreator.h"

BETTER_ENUM(DataCreatureEvol, size_t, BadMiss, Bad, Normal, Good )

BETTER_ENUM(DataCreatureClass, size_t,
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
)

BETTER_ENUM(DataCreatureGender, size_t,
    None,
    Normal,
    MoreMale,
    MoreFemale,
    OnlyMale,
    OnlyFemale,
    Hermaphrodite
)

class DataCreatureMaker {
    public:
    using rand_tuple_t = std::tuple<int, int>;
    using CreatureBattlerStatus_map_t = std::unordered_map<data::CreatureStatus, data::CreatureBattlerStatus, data::CreatureStatus::hash>;
    using attr_factor_t = std::unordered_map<data::Attribute, float, data::Attribute::hash>;

    private:
    gameentity::DataManager datamanager_;

    gameentity::CreatureCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattlercreator_;


    void initStatuses(CreatureBattlerStatus_map_t& statuses);
    void loadStatuses();


    void calcStatuses(data::Creature& creature);
    void calcElements(data::Creature& creature,
                      const std::vector<std::string>& elements);


    void makeDataCreature(data::Creature& data_creature, std::string name, DataCreatureClass cls,
        const rand_tuple_t& rand_attrBasis, 
        const rand_tuple_t& rand_attrInfla,
        const rand_tuple_t& rand_expBasis, 
        const rand_tuple_t& rand_expInfla,
        data::CreatureCircadianRhythm creatureRhythm,
        data::CreatureLevel creatureLevel, std::string type,
        const std::vector<std::string>& elements, 
        const rand_tuple_t& minmax_lvl,
        int criticalHit, int hitRate, float evol_weight, float bodysize,
        DataCreatureGender gender = DataCreatureGender::Normal);

    void saveCreature(data::Creature& creature);

    int getLeveltoEvol(data::CreatureLevel creatureLevel);



    void updateEvolutionCond(data::Creature& data_creature,
                             const std::vector<std::string>& prevs);
    void updateEvolutionNextPrev(data::Creature& data_creature,
                                 const std::vector<std::string>& nexts);
    void updateEvolutionMissPrev(data::Creature& data_creature,
                                 const std::vector<std::string>& misses);
    void updateEvolution(data::Creature& data_creature,
                         const std::vector<std::string>& nexts);
    void updateEvolution(data::Creature& data_creature,
                         const std::vector<std::string>& nexts,
                         const std::vector<std::string>& misses);
    void updateCreature(data::Creature& data_creature);





    void makeStarter();

    void makeRootType(std::string name);
    void makeType(std::string name, std::string root_name);
    void makeElement(std::string name);

    void makeTypes();
    void makeElements();
    void makeStatuses();

    public:
    void
    makeDataCreature(std::string name, std::string type, DataCreatureEvol state,
                     DataCreatureClass cls, 
                     const std::vector<std::string>& elements,
                     data::CreatureCircadianRhythm creatureRhythm,
                     data::CreatureLevel creatureLevel, float evol_weight, float bodysize,
                     DataCreatureGender gender = DataCreatureGender::Normal);

    void updateEvolution(std::string name, const std::vector<std::string>& nexts);
    void updateEvolution(std::string name, const std::vector<std::string>& nexts,
                         const std::vector<std::string>& misses);


    DataCreatureMaker();


    void initBeforData();
    void initAfterData();

    void reloadData();
    void reloadDataOnce();
};

#endif // DATACREATUREMAKER_HPP_
