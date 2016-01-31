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
      m_stepSound.setVolume(25.0f);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/theme1.wav");
      m_themeSound.setBuffer(*buffer);
      m_themeSound.setLoop(true);
      m_themeSound.setVolume(50.0f);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/fail.wav");
      m_failSound.setBuffer(*buffer);
      m_failSound.setVolume(100.0f);
    }
    
    {
      sf::SoundBuffer* buffer = gResourceManager().getSoundBuffer("sounds/door_open.wav");
      m_doorSound.setBuffer(*buffer);
      m_doorSound.setLoop(false);
      m_doorSound.setVolume(100.0f);
    }

    // Register event 
    gEventManager().registerHandler<HeroRunningEvent>(&SoundManager::onHeroRunningEvent, this);
    gEventManager().registerHandler<NewLevelEvent>(&SoundManager::onNewLevelEvent, this);
    gEventManager().registerHandler<FailSequenceEvent>(&SoundManager::onFailSequenceEvent, this);
    gEventManager().registerHandler<DoorOpeningEvent>(&SoundManager::onDoorOpeningEvent, this);
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

    m_themeSound.play();

    return game::EventStatus::KEEP;
  }

  game::EventStatus SoundManager::onFailSequenceEvent(game::EventType type, game::Event *event) {
    

    if (m_failSound.getStatus() != sf::SoundSource::Playing) {
      m_failSound.play();
    }

    return game::EventStatus::KEEP;
  }
  
  game::EventStatus SoundManager::onDoorOpeningEvent(game::EventType type, game::Event *event) {
    

    if (m_doorSound.getStatus() != sf::SoundSource::Playing) {
      m_doorSound.play();
    }

    return game::EventStatus::KEEP;
  }

}
