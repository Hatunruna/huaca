#include "WallManager.h"

#include <iostream>

#include "Constants.h"

namespace huaca {

  void WallManager::addWall(sf::Vector2f coordTile, std::size_t tile) {
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
    quad[0].color = sf::Color::Green;
    quad[1].color = sf::Color::Green;
    quad[2].color = sf::Color::Green;
    quad[3].color = sf::Color::Green;

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
