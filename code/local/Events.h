#ifndef LOCAL_EVENTS_H
#define LOCAL_EVENTS_H

#include "game/Event.h"

namespace huaca {

  struct HeroPositionEvent : public game::Event {
    static constexpr game::EventType type = "HeroPositionEvent"_type;

    sf::Vector2f pos;
  };

}


#endif // LOCAL_EVENTS_H
