#ifndef LOCAL_ITEM_HUD_H
#define LOCAL_ITEM_HUD_H

#include "game/Entity.h"

#include "Events.h"

namespace huaca {

  class ItemHUD : public game::Entity {
  public:
    ItemHUD();

    game::EventStatus onKeyLootEvent(game::EventType type, game::Event *event);
    game::EventStatus onResetLevelEvent(game::EventType type, game::Event *event);
    game::EventStatus onRunePressedEvent(game::EventType type, game::Event *event);
    game::EventStatus onFailSequenceEvent(game::EventType type, game::Event *event);
    game::EventStatus onPortalDropEvent(game::EventType type, game::Event *event);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::Texture *m_portalTexture;

    bool m_portal0;
    bool m_portal1;

    sf::Texture *m_key0Texture;
    sf::Texture *m_key1Texture;
    sf::Texture *m_key2Texture;
    sf::Texture *m_key3Texture;

    bool m_key0;
    bool m_key1;
    bool m_key2;
    bool m_key3;

    sf::Texture *m_rune0Texture;
    sf::Texture *m_rune1Texture;
    sf::Texture *m_rune2Texture;
    sf::Texture *m_rune3Texture;

    bool m_rune0;
    bool m_rune1;
    bool m_rune2;
    bool m_rune3;

  private:
    void clearRunes();

  };

}

#endif // LOCAL_ITEM_HUD_H
