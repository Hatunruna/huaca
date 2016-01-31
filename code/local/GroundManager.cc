#include "GroundManager.h"
#include "Singletons.h"
#include "Constants.h"

namespace huaca {
    
  static constexpr int TILEWIDTH = 256;
  static constexpr int TILEHEIGHT = 128;
  
  GroundManager::GroundManager()  
  : game::Entity(1)
  , m_vertices(sf::Quads) {
    // Load resources
    {
      auto texture = gResourceManager().getTexture("images/groundWalls.png");
      texture->setSmooth(true);
      m_groundsWallsTexture = texture;
    }
  }

  void GroundManager::clear() {
    m_vertices.clear();
    m_bodies.clear();
  }

  void GroundManager::addGround(sf::Vector2f coordTile, std::size_t tile) {
    // Add the bodies
    sf::FloatRect rect(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    m_bodies.push_back(rect);

    // Define new vertex
    sf::Vertex quad[4];

    // Define position
    quad[0].position = sf::Vector2f(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE);
    quad[1].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, coordTile.y * TILE_SIZE);
    quad[2].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(coordTile.x * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);

    // Define texture
    int randNb = m_random.computeUniformInteger(0,6);
    quad[0].texCoords = sf::Vector2f((randNb) * TILEWIDTH, 0);
    quad[1].texCoords = sf::Vector2f((randNb + 1) * TILEWIDTH, 0);
    quad[2].texCoords = sf::Vector2f((randNb + 1) * TILEWIDTH, TILEWIDTH);
    quad[3].texCoords = sf::Vector2f((randNb) * TILEWIDTH, TILEWIDTH);

    for (int i = 0; i < 4; ++i) {
      m_vertices.append(quad[i]);
    }
  }

  void GroundManager::addHalfWall(sf::Vector2f coordTile, std::size_t tile) {
    // Add the bodies
    sf::FloatRect rect(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    m_bodies.push_back(rect);

    // Define new vertex
    sf::Vertex quad[4];

    // Define position
    quad[0].position = sf::Vector2f(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE + TILE_SIZE/2);
    quad[1].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, coordTile.y * TILE_SIZE + TILE_SIZE/2);
    quad[2].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(coordTile.x * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);

    // Define texture
    int randNb = m_random.computeUniformInteger(0,4);
    quad[0].texCoords = sf::Vector2f((randNb) * TILEWIDTH, TILEWIDTH);
    quad[1].texCoords = sf::Vector2f((randNb + 1) * TILEWIDTH, TILEWIDTH);
    quad[2].texCoords = sf::Vector2f((randNb + 1) * TILEWIDTH, TILEHEIGHT + TILEWIDTH);
    quad[3].texCoords = sf::Vector2f((randNb) * TILEWIDTH, TILEHEIGHT + TILEWIDTH);

    for (int i = 0; i < 4; ++i) {
      m_vertices.append(quad[i]);
    }
  }

  void GroundManager::update(float dt) {

  }

  void GroundManager::render(sf::RenderWindow& window) {
    sf::RenderStates states;
    states.texture = m_groundsWallsTexture;
    window.draw(m_vertices, states);
  }

}

