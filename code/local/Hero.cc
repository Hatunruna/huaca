#include "Hero.h"

namespace huaca {

  Hero::Hero()
  : game::Entity(3)
  {

  }

  void Hero::update(float dt) {

  }

  void Hero::render(sf::RenderWindow& window) {
    sf::RectangleShape shape({ 64.0, 64.0 });
    shape.setPosition(m_pos);
    shape.setOrigin(32, 32);
    shape.setFillColor(sf::Color::Red);

    window.draw(shape);
  }

}
