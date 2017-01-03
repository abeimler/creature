#include "System/Game/CreatureGrowingIncrementListener.h"

namespace gamesystem {

CreatureGrowingIncrementListener::CreatureGrowingIncrementListener(){}

void CreatureGrowingIncrementListener::updateBodySize(
    const gameevent::ProgressTimerIncrementEvent& increment_event,
    gamecomp::CreatureBodyComponent& body, gamecomp::CreatureGeneComponent& gene) {
    
    auto newbodysize = std::min<data::bodysize_t>(body.bodysize + increment_event.addvalue, gene.max_bodysize);

    body.bodysize = std::max<data::bodysize_t>(0.0, newbodysize);
}


void CreatureGrowingIncrementListener::update(const gameevent::ProgressTimerIncrementEvent& event, 
    EntityManager& entities,
    EventBus& events, TimeDelta /*dt*/) {
    Component<gamecomp::CreatureGeneComponent> gene;
    Component<gamecomp::CreatureBodyComponent> body;

    for (auto entity : entities.entities_with_components(gene, body)) {
        if (event.type == +gamecomp::CreatureProgressTimerIncrement::Growing) {
            updateBodySize(event, *body.get(), *gene.get());
        }
    }
}

} // namespace gamesystem