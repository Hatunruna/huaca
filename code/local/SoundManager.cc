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
      m_themeSound.setVolume(30.0f);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/fail.wav");
      m_failSound.setBuffer(*buffer);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/rune0_yellow.wav");
      m_rune0Sound.setBuffer(*buffer);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/rune1_red.wav");
      m_rune1Sound.setBuffer(*buffer);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/rune2_green.wav");
      m_rune2Sound.setBuffer(*buffer);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/rune3_purple.wav");
      m_rune3Sound.setBuffer(*buffer);
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/key_found.wav");
      m_foundKeySound.setBuffer(*buffer);
      m_foundKeySound.setVolume(30.0f);
    }

    // Register event 
    gEventManager().registerHandler<HeroRunningEvent>(&SoundManager::onHeroRunningEvent, this);
    gEventManager().registerHandler<NewLevelEvent>(&SoundManager::onNewLevelEvent, this);
    gEventManager().registerHandler<FailSequenceEvent>(&SoundManager::onFailSequenceEvent, this);
    gEventManager().registerHandler<RunePressedEvent>(&SoundManager::onRunePressedEvent, this);
    gEventManager().registerHandler<KeyLootEvent>(&SoundManager::onKeyLootEvent, this);
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

  game::EventStatus SoundManager::onRunePressedEvent(game::EventType type, game::Event *event) {
    auto eventRune = static_cast<RunePressedEvent *>(event);

    switch (eventRune->runeNum) {
    case 0:
      if (m_rune0Sound.getStatus() != sf::SoundSource::Playing) {
        m_rune0Sound.play();
      }
      break;

    case 1:
      if (m_rune1Sound.getStatus() != sf::SoundSource::Playing) {
        m_rune1Sound.play();
      }
      break;

    case 2:
      if (m_rune2Sound.getStatus() != sf::SoundSource::Playing) {
        m_rune2Sound.play();
      }
      break;

    case 3:
      if (m_rune3Sound.getStatus() != sf::SoundSource::Playing) {
        m_rune3Sound.play();
      }
      break;

    default:
      assert(false);
    }
    

    return game::EventStatus::KEEP;
  }

  game::EventStatus SoundManager::onKeyLootEvent(game::EventType type, game::Event *event) {
    if (m_foundKeySound.getStatus() != sf::SoundSource::Playing) {
      m_foundKeySound.play();
    }

    return game::EventStatus::KEEP;
  }
}
