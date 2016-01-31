#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include "game/Entity.h"
#include "game/Animation.h"

#include "Events.h"

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

    void dropPortal();

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

    game::EventStatus onNewLevelEvent(game::EventType type, game::Event *event);
    game::EventStatus onResetLevelEvent(game::EventType type, game::Event *event);

    static sf::FloatRect hitboxFromPosition(const sf::Vector2f& pos);

  private:
    sf::Vector2f m_initialPos;
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
    game::Animation m_staticUp;
    game::Animation m_staticDown;
    game::Animation m_runRight;
    game::Animation m_runLeft;
    game::Animation m_runUp;
    game::Animation m_runDown;
    game::Animation *m_currentAnimation;
  };

}

#endif // LOCAL_HERO_H
