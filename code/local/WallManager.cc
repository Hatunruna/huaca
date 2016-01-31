#include "WallManager.h"

#include <cmath>
#include <iostream>

#include "Constants.h"
#include "Hero.h"
#include "Singletons.h"

namespace huaca {
  WallManager::WallManager() 
  : game::Entity(4)
  , m_vertices(sf::Quads) {
    // Register event 
    gEventManager().registerHandler<HeroPositionEvent>(&WallManager::onHeroPositionEvent, this);
  }

  void WallManager::clear() {
    m_vertices.clear();
    m_bodies.clear();
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
    quad[0].color = sf::Color(0x40, 0x40, 0x40);
    quad[1].color = sf::Color(0x40, 0x40, 0x40);
    quad[2].color = sf::Color(0x40, 0x40, 0x40);
    quad[3].color = sf::Color(0x40, 0x40, 0x40);

    for (int i = 0; i < 4; ++i) {
      m_vertices.append(quad[i]);
    }
  }

  static sf::Vector2f center(const sf::FloatRect& rect) {
    return { rect.left + rect.width / 2, rect.top + rect.height / 2 };
  }

  game::EventStatus WallManager::onHeroPositionEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<HeroPositionEvent *>(event);


    for (sf::FloatRect wall : m_bodies) {
      auto hitboxHero = Hero::hitboxFromPosition(positionEvent->pos);

      sf::FloatRect inter;

      if (wall.intersects(hitboxHero, inter)) {

        sf::Vector2f n = center(wall) - center(hitboxHero);

        float wall_extent = wall.width / 2.0f;
        float hero_extent = hitboxHero.width / 2.0f;

        float x_overlap = wall_extent + hero_extent - std::abs(n.x);

        if (x_overlap <= 0) {
          continue;
        }

        wall_extent = wall.height / 2.0f;
        hero_extent = hitboxHero.height / 2.0f;
        
        float y_overlap = wall_extent + hero_extent - std::abs(n.y);

        if (y_overlap <= 0) {
          continue;
        }

        sf::Vector2f normal;

        if (x_overlap < y_overlap) {
          if (n.x < 0) {
            normal = {  1.0f, 0.0f };
          } else {
            normal = { -1.0f, 0.0f };
          }

          positionEvent->pos += normal * x_overlap;
        } else {
          if (n.y < 0) {
            normal = { 0.0f,  1.0f };
          } else {
            normal = { 0.0f, -1.0f };
          }

          positionEvent->pos += normal * y_overlap;
        }
      }
    }

    return game::EventStatus::KEEP;
  }

  void WallManager::update(float dt) {

  }

  void WallManager::render(sf::RenderWindow& window) {
    window.draw(m_vertices);
  }

}
