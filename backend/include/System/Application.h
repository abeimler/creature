#ifndef APPLICATION_GAME_SYSTEM_H_
#define APPLICATION_GAME_SYSTEM_H_

#include "basic.h"

#include "System/Events.h"
#include "System/System.h"

namespace gamesystem {

class Application {
    private:
    System::EntityManager entities_;
    System::EventBus events_;
    std::vector<std::shared_ptr<System>> systems_;

    public:
    Application() = default;
    virtual ~Application() = default;
    Application(const Application&) = default;
    Application& operator=(const Application&) = default;
    Application(Application&&) = default;
    Application& operator=(Application&&) = default;

    System::EntityManager& getEntityManager() { return this->entities_; }
    const System::EntityManager& getEntityManager() const { return this->entities_; }

    System::EventBus& getEventBus() { return this->events_; }
    const System::EventBus& getEventBus() const { return this->events_; }


    void addSystem(const std::shared_ptr<System>& system) {
        this->systems_.push_back(system);
    }

    template<class Event>
    void addListener(const std::shared_ptr<Listener<Event>>& listener) {
        this->events_.reg(listener);
        this->systems_.emplace_back(listener);
    }

    /*
    template<typename T, typename... Args>
    void addSystem(Args&&... args) {
        auto system = std::make_shared<T>( std::forward<Args>(args)... );
        this->addSystem(system);
    }

    template<typename T, typename... Args>
    void addListener(Args&&... args) {
        auto listener = std::make_shared<T>( std::forward<Args>(args)... );
        this->addListener(listener);
    }
    */
    
    /*
    template<class Event>
    void add(const std::shared_ptr<Listener<Event>>& listener) {
        this->addListener(listener);
    }

    void add(const std::shared_ptr<System>& system) {
        this->addSystem(system);
    }

    template<typename T, typename... Args>
    void add(Args&&... args) {
        auto system_listener = std::make_shared<T>( std::forward<Args>(args)... );
        this->add(system_listener);
    }
    */
    
    

    void update(TimeDelta dt) {
        for (auto& system : this->systems_) {
            system->update(this->entities_, this->events_, dt);
        }
    }

    template<class Event>
    void emit_event(System::EventBus& events, const Event& e){
        System::emit_event<Event>(this->events_, e);
    }

    template <class Event, typename ...Args> 
    void emit_event(Args && ...args){
        System::emit_event<Event>(this->events_, std::forward<Args>(args)...);
    }
};

} // namespace gamesystem


#endif // APPLICATION_GAME_SYSTEM_H_
