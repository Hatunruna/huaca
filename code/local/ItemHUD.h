#ifndef LOCAL_ITEM_HUD_H
#define LOCAL_ITEM_HUD_H

#include "game/Entity.h"

namespace huaca {

  class ItemHUD : public game::Entity {
  public:
    ItemHUD();

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    bool m_portal0;
    bool m_portal1;

    bool m_key0;
    bool m_key1;
    bool m_key2;
    bool m_key3;

    bool m_rune0;
    bool m_rune1;
    bool m_rune2;
    bool m_rune3;
  };

}

#endif // LOCAL_ITEM_HUD_H