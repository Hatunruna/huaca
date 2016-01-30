#include "Hero.h"

#include <iostream>
#include <cassert>

#include "Constants.h"
#include "Events.h"
#include "Singletons.h"

namespace huaca {

  static constexpr int TEXTURE_SIZE = 256;

  static constexpr float SPEED = 100.0f;

  Hero::Hero(const sf::Vector2f& initialPos)
  : game::Entity(3)
  , m_pos(initialPos)
  , m_dir(Direction::RIGHT)
  , m_isRunning(false)
  , m_staticRight("Static right")
  , m_staticLeft("Static left")
  , m_currentAnimation(&m_staticRight)
  {
    {
      auto texture = gResourceManager().getTexture("static_right.png");
      m_staticRight.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }

    {
      auto texture = gResourceManager().getTexture("static_left.png");
      m_staticLeft.addFrame(texture, { 0, 0, TEXTURE_SIZE, TEXTURE_SIZE }, 1.0f);
    }
  }

  void Hero::update(float dt) {
    switch (m_dir) {
      case Direction::RIGHT:
        if (m_isRunning) {
          m_pos.x += SPEED * dt;
        }

        m_currentAnimation = &m_staticRight;
        break;

      case Direction::LEFT:
        if (m_isRunning) {
          m_pos.x -= SPEED * dt;
        }

        m_currentAnimation = &m_staticLeft;
        break;

      case Direction::UP:
        if (m_isRunning) {
          m_pos.y -= SPEED * dt;
        }

        break;

      case Direction::DOWN:
        if (m_isRunning) {
          m_pos.y += SPEED * dt;
        }

        break;
    }

    m_currentAnimation->update(dt);

    HeroPositionEvent event;
    event.pos = m_pos;

    //std::cout << "Before: " << m_pos.x << " x " << m_pos.y << std::endl;
    gEventManager().triggerEvent(&event);

    m_pos = event.pos;

    //std::cout << "After: " << m_pos.x << " x " << m_pos.y << std::endl;
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
    rect.left = pos.x - TILE_SIZE / 6;
    rect.top = pos.y + TILE_SIZE / 12;
    rect.width = TILE_SIZE / 3;
    rect.height = TILE_SIZE / 2;
    return rect;
  }

}
