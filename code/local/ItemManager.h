#ifndef LOCAL_ITEM_MANAGER_H
#define LOCAL_ITEM_MANAGER_H

#include "game/Entity.h"

namespace huaca {

  class Key {

  };

  class Rune {

  };

  class Door {

  };

  class Portal {

  };

  class ItemManager : public game::Entity {
  public:

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:

  };

}

#endif // LOCAL_ITEM_MANAGER_H
