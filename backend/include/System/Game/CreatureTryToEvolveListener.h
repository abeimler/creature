#ifndef SYSTEM_GAME_CREATURETRYTOEVOLVELISTENER_H_
#define SYSTEM_GAME_CREATURETRYTOEVOLVELISTENER_H_

#include "basic.h"

#include "Data/Basic.h"

#include "Entity/Data/DataManager.h"

#include "System/System.h"

namespace gamesystem {


class CreatureTryToEvolveListener : public Listener<gameevent::CreatureTryToEvolveEvent> {
    private:
    gamecomputil::ProgressTimerUtil progresstimer_util_;
    computil::DateTimerUtil datetimer_util_;
    gameentity::CreatureEntityCreator creaturecreator_;
    gameentity::CreatureBattlerCreator creaturebattler_creator_;

    gameentity::DataManager& datamanager_;


    bool hasNextCreatureEvolutionConditionTrainingTime(const gamecomp::CreatureDataComponent& creature_data,
                                                       data::CreatureTrainTime trainin);
    

    bool haveEvolutionCondition(const gamecomp::CreatureBattlerComponent& creature_battler,
                                const gamecomp::CreatureTrainingComponent& training,
                                const gamecomp::CreaturePsycheComponent& psyche,
                                const gamecomp::CreatureBodyComponent& body,
                                const gamecomp::CreatureBodilyStateComponent& bodilystate,
                                const data::EvolutionCondition& condition);

    void tryEvolve(gameentity::Entity entity, EventBus& events,
                    gamecomp::CreatureDataComponent& creature_data,
                    gamecomp::CreatureBattlerComponent& creature_battler,
                    gamecomp::CreatureTrainingComponent& training,
                    gamecomp::CreaturePsycheComponent& psyche,
                    gamecomp::CreatureBodyComponent& body,
                    gamecomp::CreatureBodilyStateComponent& bodilystate,
                    bool& isEvol,
                    size_t nextcreatures_index, size_t nextcreatures_size, const data::Creature& nextcreature, 
                    bool goodevolve);

    
    void tryEvolveFromList(gameentity::Entity entity, EventBus& events,
                            const std::vector<std::string>& nextcreatures,
                            gamecomp::CreatureDataComponent& creature_data,
                            gamecomp::CreatureBattlerComponent& creature_battler,
                            gamecomp::CreatureTrainingComponent& training,
                            gamecomp::CreaturePsycheComponent& psyche,
                            gamecomp::CreatureBodyComponent& body,
                            gamecomp::CreatureBodilyStateComponent& bodilystate,
                            bool& isEvol,
                            bool goodevolve);

    public:

    CreatureTryToEvolveListener(gameentity::DataManager& datamanager);

    void tryToEvolve(gameentity::Entity entity, EventBus& events,
                     gamecomp::CreatureProgressTimersComponent& timers,
                     gamecomp::CreatureDataComponent& creature_data,
                     gamecomp::CreatureGeneComponent& gene,
                     gamecomp::CreatureBattlerGeneComponent& creature_battlergene,
                     gamecomp::CreatureBattlerComponent& creature_battler,
                     gamecomp::CreatureTrainingComponent& training,
                     gamecomp::CreatureBodyComponent& body,
                     gamecomp::CreatureBodilyStateComponent& bodilystate,
                     gamecomp::CreaturePsycheComponent& psyche,
                     gamecomp::CreatureLifeComponent& life,
                     gamecomp::CreatureEvolveComponent& evolve);

    
    void update(const gameevent::CreatureTryToEvolveEvent& event,
                EntityManager& entities, EventBus& events,
                TimeDelta dt) override;

};
} // namespace gamesystem

#endif // SYSTEM_GAME_CREATURETRYTOEVOLVELISTENER_H_
