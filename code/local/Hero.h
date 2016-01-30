#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include "game/Entity.h"
#include "game/Animation.h"

namespace huaca {

  class Hero : public game::Entity {
  public:
    Hero(const sf::Vector2f& initialPos);

    void goRight() {
      m_isRunning = true;
      m_dir = Direction::RIGHT;
    }

    void goLeft() {
      m_isRunning = true;
      m_dir = Direction::LEFT;
    }

    void goUp() {
      m_isRunning = true;
      m_dir = Direction::UP;
    }

    void goDown() {
      m_isRunning = true;
      m_dir = Direction::DOWN;
    }

    void stop() {
      m_isRunning = false;
    }

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::Vector2f m_pos;

    enum class Direction {
      RIGHT,
      LEFT,
      UP,
      DOWN,
    };

    Direction m_dir;
    bool m_isRunning;

    game::Animation m_staticRight;
    game::Animation m_staticLeft;
    game::Animation *m_currentAnimation;
  };

}

#endif // LOCAL_HERO_H
