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
    int randNb = m_random.computeUniformInteger(0,20);
    if(randNb > 6){
        randNb = 0;
    }

    int x_coor = 1 + randNb * TILEWIDTH;
    quad[0].texCoords = sf::Vector2f(x_coor, 1);
    quad[1].texCoords = sf::Vector2f(x_coor + TILEWIDTH, 1);
    quad[2].texCoords = sf::Vector2f(x_coor + TILEWIDTH, TILEWIDTH);
    quad[3].texCoords = sf::Vector2f(x_coor, TILEWIDTH);

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
    int x_coor = 1 + randNb * TILEWIDTH;
    int y_coor = 2 + TILEWIDTH;
    quad[0].texCoords = sf::Vector2f(x_coor, y_coor);
    quad[1].texCoords = sf::Vector2f(x_coor + TILEWIDTH, y_coor);
    quad[2].texCoords = sf::Vector2f(x_coor + TILEWIDTH, y_coor + TILEHEIGHT);
    quad[3].texCoords = sf::Vector2f(x_coor, y_coor + TILEHEIGHT);

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

