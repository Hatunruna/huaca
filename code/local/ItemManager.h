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
    std::vector<Key*> m_keys;
    std::vector<Rune*> m_runes;
    std::vector<Door*> m_doors;
    std::vector<Portal*> m_portals;

  };

}

#endif // LOCAL_ITEM_MANAGER_H
