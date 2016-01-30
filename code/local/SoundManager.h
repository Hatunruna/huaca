#ifndef LOCAL_SOUND_MANAGER_H
#define LOCAL_SOUND_MANAGER_H

#include <SFML/Audio.hpp>

#include "Events.h"

namespace huaca {

  class SoundManager {
  public:
    SoundManager();

    game::EventStatus onHeroRunningEvent(game::EventType type, game::Event *event);

  private: 
    sf::Sound m_stepSound;
    bool m_stepPlaying;
    
  };

}

#endif // LOCAL_SOUND_MANAGER_H
