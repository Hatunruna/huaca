#ifndef LOCAL_WALL_MANAGER_H
#define LOCAL_WALL_MANAGER_H

#include "game/Entity.h"

namespace huaca {

  class WallManager : public game::Entity {
  public:
    void addWall(sf::Vector2f coordTile, std::size_t tile);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::VertexArray m_vertices;
    std::vector<sf::FloatRect> m_bodies;

  };

}

#endif // LOCAL_WALL_MANAGER_H
