#include "GroundManager.h"

#include "Constants.h"

namespace huaca {
  GroundManager::GroundManager()  
  : game::Entity(1)
  ,  m_vertices(sf::Quads) {
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

    // Define color (DEBUG)
    quad[0].color = sf::Color::White;
    quad[1].color = sf::Color::White;
    quad[2].color = sf::Color::White;
    quad[3].color = sf::Color::White;

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
    quad[0].position = sf::Vector2f(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE);
    quad[1].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, coordTile.y * TILE_SIZE);
    quad[2].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(coordTile.x * TILE_SIZE, (coordTile.y + 1) * TILE_SIZE);

    // Define color (DEBUG)
    quad[0].color = sf::Color(0x80, 0x80, 0x80);
    quad[1].color = sf::Color(0x80, 0x80, 0x80);
    quad[2].color = sf::Color(0x80, 0x80, 0x80);
    quad[3].color = sf::Color(0x80, 0x80, 0x80);

    for (int i = 0; i < 4; ++i) {
      m_vertices.append(quad[i]);
    }
  }

  void GroundManager::update(float dt) {

  }

  void GroundManager::render(sf::RenderWindow& window) {
    window.draw(m_vertices);
  }

}

