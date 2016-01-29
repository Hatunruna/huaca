#ifndef LOCAL_WALL_MANAGER_H
#define LOCAL_WALL_MANAGER_H

#include "game/Entity.h"

namespace huaca {

  class WallManager : public game::Entity {
  public:

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:


  };

}

#endif // LOCAL_WALL_MANAGER_H
