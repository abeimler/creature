#ifndef SYSTEM_GAME_SYSTEM_H_
#define SYSTEM_GAME_SYSTEM_H_

#include <entityx/entityx.hh>

#include "basic.h"

#include "System/Events.h"
#include "System/Systems.h"

namespace gamesystem {

class Application {
    public:

    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        this->systems_.emplace_back(std::make_unique<T>( std::forward<Args>(args)... ));
    }

    void update(System::TimeDelta dt) {
        for (auto& system : this->systems_) {
            system->update(this->entities_, this->events_, dt);
        }
    }

    private:
    System::EntityManager entities_;
    System::EventManager events_;
    std::vector<std::unique_ptr<System>> systems_;
};

} // namespace gamesystem


#endif // SYSTEM_GAME_SYSTEM_H_
