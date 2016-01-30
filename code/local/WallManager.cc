#include "WallManager.h"

#include <cmath>
#include <iostream>

#include "Constants.h"
#include "Singletons.h"

namespace huaca {
  WallManager::WallManager() 
  : game::Entity(4)
  , m_vertices(sf::Quads) {
    // Register event 
    gEventManager().registerHandler<HeroPositionEvent>(&WallManager::onHeroPositionEvent, this);
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

  game::EventStatus WallManager::onHeroPositionEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<HeroPositionEvent *>(event);

    sf::FloatRect hitboxHero(positionEvent->pos.x - TILE_SIZE / 4.0, positionEvent->pos.y, TILE_SIZE / 2.0f, TILE_SIZE / 2.0f);

    for (sf::FloatRect wall : m_bodies) {
      sf::FloatRect inter;
      if (wall.intersects(hitboxHero, inter)) {
        sf::Vector2f n = sf::Vector2f((wall.left + wall.width) / 2.0f, (wall.top + wall.height) / 2.0f) - sf::Vector2f((hitboxHero.left + hitboxHero.width) / 2.0f, (hitboxHero.top + hitboxHero.height) / 2.0f);

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
        if (x_overlap > y_overlap) {
          if (n.x < 0) {
            normal = { -1.0f, 0.0f };
          } else {
            normal = {  1.0f, 0.0f };
          }

          positionEvent->pos += normal * x_overlap;
        } else {
          if (n.y < 0) {
            normal = { 0.0f, -1.0f };
          } else {
            normal = { 0.0f,  1.0f };
          }

          positionEvent->pos += normal * y_overlap;
        }
        /*if(x_overlap > 0) {
          float wall_extent = wall.height / 2.0f;
          float hero_extent = hitboxHero.height / 2.0f;

          float y_overlap = wall_extent + hero_extent - std::abs(n.y);

          if(y_overlap > 0) {
            sf::Vector2f normal;
            // Find out which axis is axis of least penetration
            if(x_overlap > y_overlap) {
              // Point towards B knowing that n points from A to B
              if(n.x < 0) {
                normal = sf::Vector2f(-1, 0);
              }
              else {
                normal = sf::Vector2f(1, 0);
              }
              positionEvent->pos.x += x_overlap * normal.x;
            }
            else {
              // Point toward B knowing that n points from A to B
              if(n.y < 0) {
                normal = sf::Vector2f(0, -1);
              }
              else {
                normal = sf::Vector2f(0, 1);
              }
              positionEvent->pos.y += y_overlap * normal.y;
            }
          }
        }*/

        /*sf::Vector2f n = sf::Vector2f(hitboxHero.left, hitboxHero.top + hitboxHero.height) - sf::Vector2f(wall.left, wall.top + wall.height);

        float wall_extent = (wall.left + wall.width - wall.left) / 2.0f;
        float hero_extent = (hitboxHero.left + hitboxHero.width - hitboxHero.left) / 2.0f;

        float x_overlap = wall_extent + hero_extent - std::abs(n.x);

        if(x_overlap > 0) {
          // Calculate half extents along x axis for each object
          float wall_extent = (wall.top + wall.height - wall.top) / 2.0f;
          float hero_extent = (hitboxHero.top + hitboxHero.height - hitboxHero.top) / 2.0f;
        
          // Calculate overlap on y axis
          float y_overlap = wall_extent + hero_extent - std::abs(n.y);
        
          // SAT test on y axis
          if(y_overlap > 0) {
            sf::Vector2f normal;
            // Find out which axis is axis of least penetration
            if(x_overlap > y_overlap) {
              // Point towards B knowing that n points from A to B
              if(n.x < 0) {
                normal = sf::Vector2f(-1, 0);
              }
              else {
                normal = sf::Vector2f(1, 0);
              }
              positionEvent->pos.x += x_overlap * normal.x;
            }
            else
            {
              // Point toward B knowing that n points from A to B
              if(n.y < 0) {
                normal = sf::Vector2f(0, -1);
              }
              else {
                normal = sf::Vector2f(0, 1);
              }
              positionEvent->pos.y += y_overlap * normal.y;
            }
          }
        }*/

        /*if (positionEvent->pos.x < wall.left) {
          positionEvent->pos.x -= inter.width + 1;
        }
        else {
          positionEvent->pos.x += inter.width + 1;
        }

        if (positionEvent->pos.y < wall.top) {
          positionEvent->pos.y += inter.height + 1;
        }
        else {
          positionEvent->pos.y -= inter.height + 1;
        }*/

        //break;
      }
    }

    return game::EventStatus::KEEP;
  }

  void WallManager::update(float dt) {

  }

  void WallManager::render(sf::RenderWindow& window) {
    window.draw(m_vertices);

    for (sf::FloatRect rect: m_bodies) {
      sf::RectangleShape rectangle;
      rectangle.setSize({rect.width, rect.height});
      rectangle.setPosition(rect.left, rect.top);
      rectangle.setFillColor(sf::Color::Magenta);

      //window.draw(rectangle);
    }
  }

}
