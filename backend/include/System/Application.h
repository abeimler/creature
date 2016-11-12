#ifndef APPLICATION_GAME_SYSTEM_H_
#define APPLICATION_GAME_SYSTEM_H_

#include "basic.h"

#include "System/Events.h"
#include "System/System.h"

namespace gamesystem {

class Application {
    public:

    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        this->systems_.emplace_back(std::make_unique<T>( std::forward<Args>(args)... ));
    }

    template<typename T, typename... Args>
    void addListener(Args&&... args) {
        auto listener = std::make_shared<T>( std::forward<Args>(args)... );
        events_.reg(listener);
        this->listeners_.emplace_back(listener);
    }

    void update(System::TimeDelta dt) {
        for (auto& system : this->systems_) {
            system->update(this->entities_, this->events_, dt);
        }
        for (auto& listener : this->listeners_) {
            listener->update(this->entities_, this->events_, dt);
        }
    }

    private:
    System::EntityManager entities_;
    System::EventBus events_;
    std::vector<std::unique_ptr<System>> systems_;
    std::vector<std::shared_ptr<Listener>> listeners_;
};

} // namespace gamesystem


#endif // APPLICATION_GAME_SYSTEM_H_
