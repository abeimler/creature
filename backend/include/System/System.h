#ifndef SYSTEM_GAME_SYSTEM_H_
#define SYSTEM_GAME_SYSTEM_H_

#include <entityx/entityx.hh>

#include "basic.h"

#include "System/Events.h"

namespace gamesystem {

using TimeDelta = double;

class System {
  public:
  using EntityManager = gameentity::EntityManager;
  using Entity = gameentity::Entity;
  
  template <typename C>
  using Component = gameentity::Component<C>;

  using EventBus = gameevent::EventBus;


  System() = default;
  virtual ~System() = default;
  System(const System&) = default;
  System& operator=(const System&) = default;
  System(System&&) = default;
  System& operator=(System&&) = default;

  virtual void update(EntityManager& entities, EventBus& events, TimeDelta dt) = 0;

  template<class Event>
  static void emit_event(EventBus& events, const Event& e){
    events.publish<Event>(e);
  }

  template <class Event, typename ...Args> 
  static void emit_event(EventBus& events, Args && ...args){
    events.publish<Event>(std::forward<Args>(args)...);
  }
};

template<class Event>
class Listener : public System {
  protected:
  std::vector<Event> events_;

  public:
  Listener() = default;
  virtual ~Listener() = default;
  Listener(const Listener&) = default;
  Listener& operator=(const Listener&) = default;
  Listener(Listener&&) = default;
  Listener& operator=(Listener&&) = default;

  void receive(const Event& ev) {
    this->events_.push_back(ev);
  }

  virtual void update(const Event& event, EntityManager& entities, EventBus& events, TimeDelta dt) = 0;

  void update(EntityManager& entities, EventBus& events, TimeDelta dt) override final {
    for(const auto& event : this->events_) {
      update(event, entities, events, dt);
    }
    this->events_.clear();
  }
};

} // namespace gamesystem


#endif // SYSTEM_GAME_SYSTEM_H_
