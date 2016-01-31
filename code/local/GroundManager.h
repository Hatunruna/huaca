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

    GroundManager(const GroundManager&) = delete;
    GroundManager& operator=(const GroundManager&) = delete;

    GroundManager(GroundManager&& other) = default;
    GroundManager& operator=(GroundManager&& other) = default;

    void clear();

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
