#include "WallManager.h"

#include <iostream>

#include "Constants.h"

namespace huaca {
  WallManager::WallManager() 
  : game::Entity(4)
  , m_vertices(sf::Quads) {
  }

  void WallManager::addWall(sf::Vector2f coordTile, std::size_t tile) {
    // Add the bodies
    sf::FloatRect rect(coordTile.x * TILE_SIZE, coordTile.y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    m_bodies.push_back(rect);

    // Define new vertex
    sf::Vertex quad[4];

    // Define position
    quad[0].position = sf::Vector2f(coordTile.x * TILE_SIZE, (coordTile.y - 0.5) * TILE_SIZE);
    quad[1].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, (coordTile.y - 0.5) * TILE_SIZE);
    quad[2].position = sf::Vector2f((coordTile.x + 1) * TILE_SIZE, (coordTile.y + 0.5) * TILE_SIZE);
    quad[3].position = sf::Vector2f(coordTile.x * TILE_SIZE, (coordTile.y + 0.5) * TILE_SIZE);

    // Define color (DEBUG)
    quad[0].color = sf::Color::Blue;
    quad[1].color = sf::Color::Blue;
    quad[2].color = sf::Color::Blue;
    quad[3].color = sf::Color::Blue;

    for (int i = 0; i < 4; ++i) {
      m_vertices.append(quad[i]);
    }
  }

  void WallManager::update(float dt) {

  }

  void WallManager::render(sf::RenderWindow& window) {
    window.draw(m_vertices);
  }

}
