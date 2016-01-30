#ifndef LOCAL_GROUND_MANAGER_H
#define LOCAL_GROUND_MANAGER_H

#include "game/Entity.h"

namespace huaca {

  class GroundManager : public game::Entity {
  public:
    GroundManager();

    void addGround(sf::Vector2f coordTile, std::size_t tile);
    void addHalfWall(sf::Vector2f coordTile, std::size_t tile);

    virtual void update(float dt) override;
    virtual void render(sf::RenderWindow& window) override;

  private:
    sf::VertexArray m_vertices;
    std::vector<sf::FloatRect> m_bodies;
  };

}

#endif // LOCAL_GROUND_MANAGER_H
