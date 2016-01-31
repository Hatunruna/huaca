#include "ItemHUD.h"

#include <cassert>
#include <iostream>

#include "Singletons.h"

namespace huaca {

  ItemHUD::ItemHUD()
  : game::Entity(10)
  , m_portal0(true)
  , m_portal1(true)
  , m_key0(false)
  , m_key1(false)
  , m_key2(false)
  , m_key3(false)
  , m_rune0(false)
  , m_rune1(false)
  , m_rune2(false)
  , m_rune3(false)
  {
    // Register event 
    gEventManager().registerHandler<KeyLootEvent>(&ItemHUD::onKeyLootEvent, this);
    gEventManager().registerHandler<ResetLevelEvent>(&ItemHUD::onResetLevelEvent, this);
    gEventManager().registerHandler<RunePressedEvent>(&ItemHUD::onRunePressedEvent, this);
    gEventManager().registerHandler<FailSequenceEvent>(&ItemHUD::onFailSequenceEvent, this);

    // Load texture
    m_portalTexture = gResourceManager().getTexture("images/portal.png");

    m_key0Texture = gResourceManager().getTexture("images/key_iron.png");
    m_key1Texture = gResourceManager().getTexture("images/key_bronze.png");
    m_key2Texture = gResourceManager().getTexture("images/key_silver.png");
    m_key3Texture = gResourceManager().getTexture("images/key_gold.png");

    m_rune0Texture = gResourceManager().getTexture("images/rune0_yellow.png");
    m_rune1Texture = gResourceManager().getTexture("images/rune1_red.png");
    m_rune2Texture = gResourceManager().getTexture("images/rune2_green.png");
    m_rune3Texture = gResourceManager().getTexture("images/rune3_purple.png");
  }

  game::EventStatus ItemHUD::onKeyLootEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<KeyLootEvent *>(event);

    switch (positionEvent->keyNum) {
    case 0:
      m_key0 = true;
      break;

    case 1:
      m_key1 = true;
      break;

    case 2:
      m_key2 = true;
      break;

    case 3:
      m_key3 = true;
      break;

    default:
      assert(false);
    }

    return game::EventStatus::KEEP;
  }

  game::EventStatus ItemHUD::onRunePressedEvent(game::EventType type, game::Event *event) {
    auto eventRune = static_cast<RunePressedEvent *>(event);

    switch (eventRune->runeNum) {
    case 0:
      m_rune0 = true;
      break;

    case 1:
      m_rune1 = true;
      break;

    case 2:
      m_rune2 = true;
      break;

    case 3:
      m_rune3 = true;
      break;

    default:
      assert(false);
    }

    return game::EventStatus::KEEP;
  }

  game::EventStatus ItemHUD::onResetLevelEvent(game::EventType type, game::Event *event) {
    m_portal0 = m_portal1 = true;
    m_key0 = m_key1 = m_key2 = m_key3 = false;
    m_rune0 = m_rune1 = m_rune2 = m_rune3 = false;
    clearRunes();
    return game::EventStatus::KEEP;
  }


  game::EventStatus ItemHUD::onFailSequenceEvent(game::EventType type, game::Event *event) {
    clearRunes();
    return game::EventStatus::KEEP;
  }

  void ItemHUD::update(float dt) {

  }

  static constexpr float PADDING = 20.0f;

  static constexpr float KEY_SIZE = 30.0f;
  static constexpr float KEY_TEXTURE_SIZE = 64.0f;
  static constexpr float KEY_SPACE = 10.0f;

  static constexpr float RUNE_SIZE = 50.0f;
  static constexpr float RUNE_TEXTURE_SIZE = 64.0f;
  static constexpr float RUNE_SPACE = 10.0f;

  static constexpr float PORTAL_TEXTURE_SIZE = 64.0f;
  static constexpr float PORTAL_SIZE = 40.0f;
  static constexpr float PORTAL_SPACE = 10.0f;

  void ItemHUD::render(sf::RenderWindow& window) {
    {
      float x = PADDING;
      float y = PADDING;

      sf::Sprite sprite;
      sprite.setScale(KEY_SIZE / KEY_TEXTURE_SIZE, KEY_SIZE / KEY_TEXTURE_SIZE);

      // key 0
      sprite.setTexture(*m_key0Texture);
      sprite.setPosition({ x, y });
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_key0 ? 0xFF : 0x20));
      window.draw(sprite);

      // key 1
      x += KEY_SIZE + KEY_SPACE;
      sprite.setTexture(*m_key1Texture);
      sprite.setPosition({ x, y });
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_key1 ? 0xFF : 0x20));
      window.draw(sprite);

      // key 2
      x += KEY_SIZE + KEY_SPACE;
      sprite.setTexture(*m_key2Texture);
      sprite.setPosition({ x, y });
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_key2 ? 0xFF : 0x20));
      window.draw(sprite);

      // key 3
      x += KEY_SIZE + KEY_SPACE;
      sprite.setTexture(*m_key3Texture);
      sprite.setPosition({ x, y });
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_key3 ? 0xFF : 0x20));
      window.draw(sprite);

    }

    {
      float x = PADDING;
      float y = gWindowGeometry().getYFromBottom(RUNE_SIZE + RUNE_SPACE + RUNE_SIZE + PADDING);

      sf::Sprite sprite;
      sprite.setScale(RUNE_SIZE / RUNE_TEXTURE_SIZE, RUNE_SIZE / RUNE_TEXTURE_SIZE);

      // rune 0
      sprite.setTexture(*m_rune0Texture);
      sprite.setPosition(x, y);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_rune0 ? 0xFF : 0x20));
      window.draw(sprite);

      // rune 1
      sprite.setTexture(*m_rune1Texture);
      sprite.setPosition(x + RUNE_SIZE + RUNE_SPACE, y);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_rune1 ? 0xFF : 0x20));
      window.draw(sprite);

      // rune 2
      sprite.setTexture(*m_rune2Texture);
      sprite.setPosition(x, y + RUNE_SIZE + RUNE_SPACE);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_rune2 ? 0xFF : 0x20));
      window.draw(sprite);

      // rune 3
      sprite.setTexture(*m_rune3Texture);
      sprite.setPosition(x + RUNE_SIZE + RUNE_SPACE, y + RUNE_SIZE + RUNE_SPACE);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_rune3 ? 0xFF : 0x20));
      window.draw(sprite);

    }

    {
      float x = gWindowGeometry().getXFromRight(PORTAL_SIZE + PORTAL_SPACE + PORTAL_SIZE + PADDING);
      float y = PADDING;

      sf::Sprite sprite;
      sprite.setScale(PORTAL_SIZE / PORTAL_TEXTURE_SIZE, PORTAL_SIZE / PORTAL_TEXTURE_SIZE);
      sprite.setTexture(*m_portalTexture);

      // portal 0
      sprite.setPosition(x, y);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_portal0 ? 0xFF : 0x20));
      window.draw(sprite);

      // portal 1
      sprite.setPosition(x + PORTAL_SIZE + PORTAL_SPACE, y);
      sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, m_portal1 ? 0xFF : 0x20));
      window.draw(sprite);

    }
  }

  void ItemHUD::clearRunes() {
    m_rune0 = false;
    m_rune1 = false;
    m_rune2 = false;
    m_rune3 = false;
  }

}
