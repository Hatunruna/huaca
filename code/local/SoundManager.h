#ifndef LOCAL_SOUND_MANAGER_H
#define LOCAL_SOUND_MANAGER_H

#include <SFML/Audio.hpp>

#include "Events.h"

namespace huaca {

  class SoundManager {
  public:
    SoundManager();

    game::EventStatus onHeroRunningEvent(game::EventType type, game::Event *event);
    game::EventStatus onNewLevelEvent(game::EventType type, game::Event *event);
    game::EventStatus onFailSequenceEvent(game::EventType type, game::Event *event);
    game::EventStatus onRunePressedEvent(game::EventType type, game::Event *event);
    game::EventStatus onKeyLootEvent(game::EventType type, game::Event *event);
    game::EventStatus onDoorOpeningEvent(game::EventType type, game::Event *event);

  private: 
    sf::Sound m_stepSound;
    bool m_stepPlaying;

    sf::Sound m_themeSound;

    sf::Sound m_failSound;

    sf::Sound m_rune0Sound;
    sf::Sound m_rune1Sound;
    sf::Sound m_rune2Sound;
    sf::Sound m_rune3Sound;

    sf::Sound m_foundKeySound;
    sf::Sound m_doorSound;
  };

}

#endif // LOCAL_SOUND_MANAGER_H
