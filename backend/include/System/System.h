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


  using EventManager = gameevent::EventManager;
  using EventEntity = gameevent::EventEntity;

  template <typename E>
  using Event = gameevent::Event<E>;

  System() = default;
  virtual ~System() = default;
  System(const System&) = default;
  System& operator=(const System&) = default;
  System(System&&) = default;
  System& operator=(System&&) = default;

  virtual void update(EntityManager& es, EventManager& ev, TimeDelta dt) = 0;

  template<class EventComp>
  static void emit_event(EventManager& events, const EventComp& e){
    auto evententity = events.create();
    evententity.assign<EventComp>(e);
  }

  template <class EventComp, typename ...Args> 
  static void emit_event(EventManager& events, Args && ...args){
    return emit_event(events, EventComp (std::forward<Args>(args)...));
  }

  template<class EventComp>
  static Event<EventComp> get_event(EventEntity& evententity) {
    Event<EventComp> event = evententity.component<EventComp>();
    return event;
  }
};

template<class EventComp>
class Receiver : public System {
  public:
  Receiver() = default;
  virtual ~Receiver() = default;
  Receiver(const Receiver&) = default;
  Receiver& operator=(const Receiver&) = default;
  Receiver(Receiver&&) = default;
  Receiver& operator=(Receiver&&) = default;

  virtual void handle(EventComp& es, EntityManager& ev, EventManager&, TimeDelta at) = 0;

  void update(EntityManager& es, EventManager& ev, TimeDelta dt) final {
    for (auto evententity : ev.entities_with_components<EventComp>()) {
      auto event = get_event(evententity);
      if(event){
        handle(*event, es, ev, dt);
      }
      evententity.destroy();
    }  
  }
};

} // namespace gamesystem


#endif // SYSTEM_GAME_SYSTEM_H_
