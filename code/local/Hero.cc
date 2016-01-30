#include "Hero.h"

#include <iostream>
#include <cassert>

#include "Constants.h"
#include "Events.h"
#include "Singletons.h"

namespace huaca {

  static constexpr int TEXTURE_SIZE = 256;

  static constexpr float SPEED = 180.0f;
  static constexpr float FRAME_TIME = 0.05f;

  Hero::Hero(const sf::Vector2f& initialPos)
  : game::Entity(3)
  , m_pos(initialPos)
  , m_dir(Direction::RIGHT)
  , m_isRunning(false)
  , m_staticRight("Static right")
  , m_staticLeft("Static left")
  , m_staticUp("Static up")
  , m_staticDown("Static down")
  , m_runRight("Run right")
  , m_runLeft("Run left")
  , m_runUp("Run up")
  , m_runDown("Run down")
  , m_currentAnimation(&m_staticRight)
  , m_stepPlaying(false)
  {
    {
      auto texture = gResourceManager().getTexture("images/static_right.png");
      texture->setSmooth(true);
      m_staticRight.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }

    {
      auto texture = gResourceManager().getTexture("images/static_left.png");
      texture->setSmooth(true);
      m_staticLeft.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }

    {
      auto texture = gResourceManager().getTexture("images/static_up.png");
      texture->setSmooth(true);
      m_staticUp.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }

    {
      auto texture = gResourceManager().getTexture("images/static_down.png");
      texture->setSmooth(true);
      m_staticDown.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }

    {
      auto texture = gResourceManager().getTexture("images/run_right.png");
      texture->setSmooth(true);

      for (int i = 0; i < 12; ++i) {
        m_runRight.addFrame(texture, { (i % 4) * TEXTURE_SIZE, (i / 4) * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE }, FRAME_TIME);
      }
    }

    {
      auto texture = gResourceManager().getTexture("images/run_left.png");
      texture->setSmooth(true);

      for (int i = 0; i < 12; ++i) {
        m_runLeft.addFrame(texture, { (i % 4) * TEXTURE_SIZE, (i / 4) * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE }, FRAME_TIME);
      }
    }

    {
      auto texture = gResourceManager().getTexture("images/run_up.png");
      texture->setSmooth(true);

      for (int i = 0; i < 12; ++i) {
        m_runUp.addFrame(texture, { (i % 4) * TEXTURE_SIZE, (i / 4) * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE }, FRAME_TIME);
      }
    }

    {
      auto texture = gResourceManager().getTexture("images/run_down.png");
      texture->setSmooth(true);

      for (int i = 0; i < 12; ++i) {
        m_runDown.addFrame(texture, { (i % 4) * TEXTURE_SIZE, (i / 4) * TEXTURE_SIZE, TEXTURE_SIZE, TEXTURE_SIZE }, FRAME_TIME);
      }
    }

    {
      auto buffer = gResourceManager().getSoundBuffer("sounds/step.wav");
      m_stepSound.setBuffer(*buffer);
      m_stepSound.setLoop(true);
    }
  }

  void Hero::update(float dt) {
    // Manage animation
    switch (m_dir) {
      case Direction::RIGHT:
        if (m_isRunning) {
          m_pos.x += SPEED * dt;
          m_currentAnimation = &m_runRight;
        }
        else {
          m_currentAnimation = &m_staticRight;
        }
        
        break;

      case Direction::LEFT:
        if (m_isRunning) {
          m_pos.x -= SPEED * dt;
          m_currentAnimation = &m_runLeft;
        }
        else {
          m_currentAnimation = &m_staticLeft;
        }

        break;

      case Direction::UP:
        if (m_isRunning) {
          m_pos.y -= SPEED * dt;
          m_currentAnimation = &m_runUp;
        }
        else {
          m_currentAnimation = &m_staticUp;
        }

        break;

      case Direction::DOWN:
        if (m_isRunning) {
          m_pos.y += SPEED * dt;
          m_currentAnimation = &m_runDown;
        }
        else {
          m_currentAnimation = &m_staticDown;
        }

        break;
    }

    // Manage audio
    if (m_isRunning) {
      if (!m_stepPlaying) {
        m_stepPlaying = true;
        m_stepSound.play();
      }
    }
    else {
      m_stepPlaying = false;
      m_stepSound.stop();
    }

    m_currentAnimation->update(dt);

    HeroPositionEvent event;
    event.pos = m_pos;

    gEventManager().triggerEvent(&event);

    m_pos = event.pos;
  }

  void Hero::render(sf::RenderWindow& window) {
    auto rect = hitboxFromPosition(m_pos);

    sf::RectangleShape hitbox({ rect.width, rect.height });
    hitbox.setPosition(rect.left, rect.top);
    hitbox.setFillColor(sf::Color::Red);
    window.draw(hitbox);

    assert(m_currentAnimation);
    m_currentAnimation->renderAt(window, m_pos, 0.0f, static_cast<float>(TILE_SIZE) / TEXTURE_SIZE);
  }

  sf::FloatRect Hero::hitboxFromPosition(const sf::Vector2f& pos) {
    sf::FloatRect rect;
    rect.left = pos.x - TILE_SIZE / 4 - 2;
    rect.top = pos.y + TILE_SIZE / 12;
    rect.width = TILE_SIZE / 2;
    rect.height = TILE_SIZE / 2;
    return rect;
  }

}
