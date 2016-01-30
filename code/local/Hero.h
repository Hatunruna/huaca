#ifndef LOCAL_HERO_H
#define LOCAL_HERO_H

#include "game/Entity.h"

namespace huaca {

  class Hero : public game::Entity {
  public:
    Hero();

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::Vector2f m_pos;

  };

}

#endif // LOCAL_HERO_H
