#include "ItemManager.h"

#include <cassert>
#include <iostream>

#include "Constants.h"
#include "Singletons.h"

namespace huaca {
  static constexpr float KEY_SIZE = 30.0f;
  static constexpr float KEY_TEXTURE_SIZE = 64.0f;

  ItemManager::ItemManager()
  : game::Entity(2)
  , m_currentKey(0) {
    // Load resources
    {
      auto texture = gResourceManager().getTexture("images/key_iron.png");
      texture->setSmooth(true);
      m_ironKeyTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/key_bronze.png");
      texture->setSmooth(true);
      m_bronzeKeyTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/key_silver.png");
      texture->setSmooth(true);
      m_silverKeyTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/key_gold.png");
      texture->setSmooth(true);
      m_goldKeyTexture = texture;
    }
  }

  void ItemManager::addKey(sf::Vector2i pos) {
    Key key;

    switch (m_currentKey) {
    case 0:
      key.texture = m_ironKeyTexture;
      break;

    case 1:
      key.texture = m_bronzeKeyTexture;
      break;

    case 2:
      key.texture = m_silverKeyTexture;
      break;

    case 3:
      key.texture = m_goldKeyTexture;
      break;

    default:
      assert(false);
    }

    key.pos = sf::Vector2f(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
    key.isActive = true;

    m_keys.push_back(key);

    ++m_currentKey;
  }

  void ItemManager::update(float dt) {

  }

  void ItemManager::render(sf::RenderWindow& window) {
    // Render the keys
    for (Key key : m_keys) {
      if (!key.isActive) {
        continue;
      }

      sf::Sprite sprite;
      sprite.setScale(KEY_SIZE / KEY_TEXTURE_SIZE, KEY_SIZE / KEY_TEXTURE_SIZE);

      sprite.setTexture(*key.texture);
      sprite.setPosition(key.pos);

      window.draw(sprite);
    }
  }

}

