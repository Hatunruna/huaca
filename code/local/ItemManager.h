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

  };

  struct Door {
    sf::Texture *texture;
    sf::Vector2f pos;
    sf::FloatRect hitbox;
    unsigned int num;
    bool isActive;
    bool isOpen;
    bool isVertical;
  };

  struct Portal {

  };

  class ItemManager : public game::Entity {
  public:
    ItemManager();

    void addKey(sf::Vector2i pos);
    void addDoor(sf::Vector2i pos, bool isVertical);

    game::EventStatus onHeroPositionEvent(game::EventType type, game::Event *event);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

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
  };

}

#endif // LOCAL_ITEM_MANAGER_H
