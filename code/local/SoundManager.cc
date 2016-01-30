#include "SoundManager.h"

#include "Singletons.h"

namespace huaca {

  SoundManager::SoundManager() 
  : m_stepPlaying(false) {
    // Load ressources
    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/step.wav");
      m_stepSound.setBuffer(*buffer);
      m_stepSound.setLoop(true);
    }

    // Register event 
    gEventManager().registerHandler<HeroRunningEvent>(&SoundManager::onHeroRunningEvent, this);
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

}
