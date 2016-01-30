#ifndef LOCAL_EVENTS_H
#define LOCAL_EVENTS_H

#include "game/Event.h"

namespace huaca {

  struct HeroPositionEvent : public game::Event {
    static constexpr game::EventType type = "HeroPositionEvent"_type;

    sf::Vector2f pos;
  };

  struct HeroRunningEvent : public game::Event {
    static constexpr game::EventType type = "HeroRunningEvent"_type;

    bool isRunning;
  };

  struct NewLevelEvent : public game::Event {
    static constexpr game::EventType type = "NewLevelEvent"_type;

    sf::Vector2f posHero;
  };

}


#endif // LOCAL_EVENTS_H
