#include "ItemHUD.h"

#include "Singletons.h"

namespace huaca {

  ItemHUD::ItemHUD()
  : game::Entity(10)
  , m_portal0(false)
  , m_portal1(true)
  , m_key0(true)
  , m_key1(true)
  , m_key2(false)
  , m_key3(true)
  , m_rune0(true)
  , m_rune1(true)
  , m_rune2(false)
  , m_rune3(true)
  {

  }

  void ItemHUD::update(float dt) {

  }

  static constexpr float PADDING = 20.0f;

  static constexpr float KEY_WIDTH = 10.0f;
  static constexpr float KEY_HEIGHT = 40.0f;
  static constexpr float KEY_SPACE = 15.0f;

  static constexpr float RUNE_SIZE = 30.0f;
  static constexpr float RUNE_SPACE = 10.0f;

  static constexpr float PORTAL_RADIUS = 20.0f;
  static constexpr float PORTAL_SPACE = 10.0f;

  void ItemHUD::render(sf::RenderWindow& window) {
    {
      float x = PADDING;
      float y = PADDING;

      for (auto key : { m_key0, m_key1, m_key2, m_key3 }) {
        sf::RectangleShape shape({ KEY_WIDTH, KEY_HEIGHT });
        shape.setPosition({ x, y });
        shape.setFillColor(sf::Color(0x00, 0xFF, 0x00, key ? 0xFF : 0x20));
        window.draw(shape);

        x += KEY_WIDTH + KEY_SPACE;
      }

      {
        float x = PADDING;
        float y = gWindowGeometry().getYFromBottom(RUNE_SIZE + RUNE_SPACE + RUNE_SIZE + PADDING);

        sf::RectangleShape shape({ RUNE_SIZE, RUNE_SIZE });

        // rune 0
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(0xFF, 0x00, 0x00, m_rune0 ? 0xFF : 0x20));
        window.draw(shape);

        // rune 1
        shape.setPosition(x + RUNE_SIZE + RUNE_SPACE, y);
        shape.setFillColor(sf::Color(0x00, 0xFF, 0x00, m_rune1 ? 0xFF : 0x20));
        window.draw(shape);

        // rune 2
        shape.setPosition(x, y + RUNE_SIZE + RUNE_SPACE);
        shape.setFillColor(sf::Color(0x00, 0x00, 0xFF, m_rune2 ? 0xFF : 0x20));
        window.draw(shape);

        // rune 3
        shape.setPosition(x + RUNE_SIZE + RUNE_SPACE, y + RUNE_SIZE + RUNE_SPACE);
        shape.setFillColor(sf::Color(0xFF, 0xFF, 0x00, m_rune3 ? 0xFF : 0x20));
        window.draw(shape);

      }

      {
        float x = gWindowGeometry().getXFromRight(PORTAL_RADIUS * 2 + PORTAL_SPACE + PORTAL_RADIUS * 2 + PADDING);
        float y = PADDING;

        sf::CircleShape shape(PORTAL_RADIUS);

        // portal 0
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color(0xFF, 0x80, 0x00, m_portal0 ? 0xFF : 0x20));
        window.draw(shape);

        // portal 1
        shape.setPosition(x + PORTAL_RADIUS * 2 + PORTAL_SPACE, y);
        shape.setFillColor(sf::Color(0xFF, 0x80, 0x00, m_portal1 ? 0xFF : 0x20));
        window.draw(shape);

      }

    }


  }

}
