#ifndef LOCAL_WALL_MANAGER_H
#define LOCAL_WALL_MANAGER_H

#include "game/Entity.h"

#include "Events.h"

namespace huaca {

  class WallManager : public game::Entity {
  public:
    WallManager();

    WallManager(const WallManager&) = delete;
    WallManager& operator=(const WallManager&) = delete;

    WallManager(WallManager&& other) = default;
    WallManager& operator=(WallManager&& other) = default;

    void addWall(sf::Vector2f coordTile, std::size_t tile);

    game::EventStatus onHeroPositionEvent(game::EventType type, game::Event *event);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::VertexArray m_vertices;
    std::vector<sf::FloatRect> m_bodies;

  };

}

#endif // LOCAL_WALL_MANAGER_H
