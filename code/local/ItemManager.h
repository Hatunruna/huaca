#ifndef LOCAL_ITEM_MANAGER_H
#define LOCAL_ITEM_MANAGER_H

#include "game/Entity.h"

#include "Events.h"

namespace huaca {

  struct Key {
    sf::Texture *texture;
    sf::Vector2f pos;
    sf::FloatRect hitbox;
    unsigned int num;
    bool isActive;
    bool isLooted;
  };

  struct Rune {
    sf::Texture *texture;
    sf::Vector2f pos;
    sf::FloatRect hitbox;
    unsigned int num;
    bool isActive;
    bool isPressed;
  };

  struct Door {
    sf::Texture *texture;
    sf::Vector2f pos;
    sf::FloatRect hitbox;
    unsigned int num;
    bool keyFound;
    bool isOpen;
    bool isVertical;
  };

  struct Portal {
    sf::Texture *texture;
    sf::Vector2f pos;
    sf::FloatRect hitbox;
    unsigned int num;
  };

  class ItemManager : public game::Entity {
  public:
    ItemManager();

    void clear();
    void setRuneOrder(const int runeOrder[4]);

    ItemManager(const ItemManager&) = delete;
    ItemManager& operator=(const ItemManager&) = delete;

    ItemManager(ItemManager&& other) = default;
    ItemManager& operator=(ItemManager&& other) = default;

    void addKey(sf::Vector2i pos);
    void addDoor(sf::Vector2i pos, bool isVertical);
    void addRune(sf::Vector2i pos);

    game::EventStatus onHeroPositionEvent(game::EventType type, game::Event *event);
    game::EventStatus onKeyLootEvent(game::EventType type, game::Event *event);
    game::EventStatus onResetLevelEvent(game::EventType type, game::Event *event);
    game::EventStatus onPortalDropEvent(game::EventType type, game::Event *event);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

    bool isLevelFinished() const {
      return m_currentOrder == 4;
    }

  private:
    std::vector<Key> m_keys;
    std::vector<Rune> m_runes;
    std::vector<Door> m_doors;
    std::vector<Portal> m_portals;

    unsigned int m_currentKey;
    sf::Texture *m_ironKeyTexture;
    sf::Texture *m_bronzeKeyTexture;
    sf::Texture *m_silverKeyTexture;
    sf::Texture *m_goldKeyTexture;

    unsigned int m_currentDoor;
    sf::Texture *m_ironDoorVerticalTexture;
    sf::Texture *m_bronzeDoorVerticalTexture;
    sf::Texture *m_silverDoorVerticalTexture;
    sf::Texture *m_goldDoorVerticalTexture;
    sf::Texture *m_ironDoorHorizontalTexture;
    sf::Texture *m_bronzeDoorHorizontalTexture;
    sf::Texture *m_silverDoorHorizontalTexture;
    sf::Texture *m_goldDoorHorizontalTexture;

    unsigned int m_currentRune;
    sf::Texture *m_rune0Texture;
    sf::Texture *m_rune1Texture;
    sf::Texture *m_rune2Texture;
    sf::Texture *m_rune3Texture;
    bool m_resetAllRunes;

    int m_runeOrder[4];
    int m_currentOrder;

    unsigned int m_currentPortal;
    bool m_isOnPortal;
    sf::Texture *m_portalTexture;

  private:
    void clearRunes();
  };

}

#endif // LOCAL_ITEM_MANAGER_H
