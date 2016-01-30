#include "SoundManager.h"

#include <iostream>

#include "Singletons.h"

namespace huaca {

  SoundManager::SoundManager() 
  : m_stepPlaying(false) {
    // Load ressources
    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/step.wav");
      m_stepSound.setBuffer(*buffer);
      m_stepSound.setLoop(true);
      m_stepSound.setVolume(75.0f);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/theme1.wav");
      m_themeSound.setBuffer(*buffer);
      m_themeSound.setLoop(true);
    }

    // Register event 
    gEventManager().registerHandler<HeroRunningEvent>(&SoundManager::onHeroRunningEvent, this);
    gEventManager().registerHandler<NewLevelEvent>(&SoundManager::onNewLevelEvent, this);
  }

  game::EventStatus SoundManager::onHeroRunningEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<HeroRunningEvent *>(event);

    if (positionEvent->isRunning) {
      if (!m_stepPlaying) {
        m_stepPlaying = true;
        m_stepSound.play();
      }
    }
    else {
      m_stepPlaying = false;
      m_stepSound.stop();
    }

    return game::EventStatus::KEEP;
  }

  game::EventStatus SoundManager::onNewLevelEvent(game::EventType type, game::Event *event) {
    std::cout << "La" << std::endl;

    m_themeSound.play();

    return game::EventStatus::KEEP;
  }

}
