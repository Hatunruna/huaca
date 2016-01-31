#ifndef LOCAL_GROUND_MANAGER_H
#define LOCAL_GROUND_MANAGER_H

#include "game/Entity.h"
#include "../game/Random.h"

namespace huaca {
    
  struct Ground {
      sf::Texture *texture;
      unsigned int num;
      sf::Vector2f coordTile;
      std::size_t tile;
  };
  
  struct HalfWall {
      sf::Texture *texture;
      unsigned int num;
      sf::Vector2f coordTile;
      std::size_t tile;
  };

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
    sf::Texture *m_groundsWallsTexture;
    game::Random m_random;
  };

}

#endif // LOCAL_GROUND_MANAGER_H
