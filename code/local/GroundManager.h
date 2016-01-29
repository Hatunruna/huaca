#ifndef LOCAL_GROUND_MANAGER_H
#define LOCAL_GROUND_MANAGER_H

#include "game/Entity.h"

namespace huaca {

  class GroundManager : public game::Entity {
  public:

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:


  };

}

#endif // LOCAL_GROUND_MANAGER_H
