#ifndef INITDATA_H_
#define INITDATA_H_

#include <memory>

#include "DataMaker/DataCreatureMaker.h"


BETTER_ENUM( DataCreatureAttribute, size_t,
    None, 
    Vaccine, 
    Data, 
    Virus,
    Free,
    Variable,
    Unknown
)

class InitData {
    private:
    datamaker::DataCreatureMaker maker_;

    std::vector<std::string> elements_;
    datamaker::DataCreatureMaker::resists_t elements_resists_;
    std::map<std::string, std::vector<std::string>> types_;
    
    static inline datamaker::DataCreatureMaker::resists_value_t make_resists_value(const std::vector<std::string>& a,const std::vector<std::string>& b) {
        return datamaker::DataCreatureMaker::make_resists_value(a, b);
    }

    void
    makeDataCreature(std::string name, std::string type, datamaker::DataCreatureEvol state,
                     datamaker::DataCreatureClass cls, 
                     const std::vector<std::string>& elements,
                     data::CreatureCircadianRhythm creatureRhythm,
                     data::CreatureLevel creatureLevel, float evol_weight,
                     float bodysize,
                     datamaker::DataCreatureGender gender = datamaker::DataCreatureGender::Normal);
                     
    void
    makeDataCreature(std::string name, std::string type, datamaker::DataCreatureEvol state,
                     datamaker::DataCreatureClass cls, 
                     const std::vector<std::string>& elements,
                     DataCreatureAttribute dataCreatureAttribute,
                     data::CreatureLevel creatureLevel, float evol_weight,
                     float bodysize,
                     datamaker::DataCreatureGender gender = datamaker::DataCreatureGender::Normal);

    void updateEvolution(std::string name, const std::vector<std::string>& nexts);
    void updateEvolution(std::string name, const std::vector<std::string>& nexts,
                         const std::vector<std::string>& misses);
    void updateEvolution(std::string name, const std::vector<std::string>& pervs,
                         const std::vector<std::string>& nexts,
                         const std::vector<std::string>& misses);

    void initElements();
    void initTypes();

    void makeCreature1();
    void makeCreature2();

    void updateCreature1();
    void updateCreature2();

    public:
    InitData();

    void makeDataCreature();

    const datamaker::DataCreatureMaker& getMaker() const { return this->maker_; }
    datamaker::DataCreatureMaker& getMaker() { return this->maker_; }
};

#endif // INITDATA_H_
