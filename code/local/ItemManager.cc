#include "ItemManager.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <SFML/Audio.hpp>

#include "Constants.h"
#include "Hero.h"
#include "Singletons.h"

namespace huaca {
  static constexpr float KEY_SIZE = 15.0f;
  static constexpr float KEY_TEXTURE_SIZE = 64.0f;

  static constexpr float DOOR_VERTICAL_SIZE_X = 6.0f;
  static constexpr float DOOR_VERTICAL_SIZE_Y = 64.0f;
  static constexpr float DOOR_VERTICAL_TEXTURE_SIZE_X = 35.0f;
  static constexpr float DOOR_VERTICAL_TEXTURE_SIZE_Y = 256.0f;

  static constexpr float DOOR_HORIZONTAL_SIZE_X = 64.0f;
  static constexpr float DOOR_HORIZONTAL_SIZE_Y = 32.0f;
  static constexpr float DOOR_HORIZONTAL_TEXTURE_SIZE_X = 256.0f;
  static constexpr float DOOR_HORIZONTAL_TEXTURE_SIZE_Y = 128.0f;

  static constexpr float RUNE_SIZE = 32.0f;
  static constexpr float RUNE_TEXTURE_SIZE = 64.0f;

  static constexpr float PORTAL_SIZE = 32.0f;
  static constexpr float PORTAL_TEXTURE_SIZE = 64.0f;

  ItemManager::ItemManager()
  : game::Entity(2)
  , m_currentKey(0)
  , m_currentDoor(0) 
  , m_currentRune(0)
  , m_currentOrder(0)
  , m_currentPortal(0)
  {
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

    {
      auto texture = gResourceManager().getTexture("images/door_iron_vertical.png");
      texture->setSmooth(true);
      m_ironDoorVerticalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_bronze_vertical.png");
      texture->setSmooth(true);
      m_bronzeDoorVerticalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_silver_vertical.png");
      texture->setSmooth(true);
      m_silverDoorVerticalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_gold_vertical.png");
      texture->setSmooth(true);
      m_goldDoorVerticalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_iron.png");
      texture->setSmooth(true);
      m_ironDoorHorizontalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_bronze.png");
      texture->setSmooth(true);
      m_bronzeDoorHorizontalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_silver.png");
      texture->setSmooth(true);
      m_silverDoorHorizontalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/door_gold.png");
      texture->setSmooth(true);
      m_goldDoorHorizontalTexture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/rune0_yellow.png");
      texture->setSmooth(true);
      m_rune0Texture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/rune1_red.png");
      texture->setSmooth(true);
      m_rune1Texture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/rune2_green.png");
      texture->setSmooth(true);
      m_rune2Texture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/rune3_purple.png");
      texture->setSmooth(true);
      m_rune3Texture = texture;
    }

    {
      auto texture = gResourceManager().getTexture("images/portal.png");
      texture->setSmooth(true);
      m_portalTexture = texture;
    }

    // Register event 
    gEventManager().registerHandler<HeroPositionEvent>(&ItemManager::onHeroPositionEvent, this);
    gEventManager().registerHandler<KeyLootEvent>(&ItemManager::onKeyLootEvent, this);
    gEventManager().registerHandler<ResetLevelEvent>(&ItemManager::onResetLevelEvent, this);
    gEventManager().registerHandler<PortalDropEvent>(&ItemManager::onPortalDropEvent, this);

  }

  void ItemManager::clear() {
    m_keys.clear();
    m_runes.clear();
    m_doors.clear();
    m_portals.clear();

    m_currentKey = 0;
    m_currentDoor = 0;
    m_currentRune = 0;
    m_currentOrder = 0;
    m_currentPortal = 0;
    m_isOnPortal = false;
  }

  void ItemManager::setRuneOrder(const int runeOrder[4]) {
    // Set the sequence rune
    std::copy(runeOrder, runeOrder + 4, m_runeOrder);
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

    key.pos = sf::Vector2f(pos.x * TILE_SIZE + TILE_SIZE / 2, pos.y * TILE_SIZE + TILE_SIZE / 2);
    key.hitbox = sf::FloatRect(
      pos.x * TILE_SIZE + TILE_SIZE / 2 - KEY_SIZE / 2,
      pos.y * TILE_SIZE + TILE_SIZE / 2 - KEY_SIZE / 2,
      KEY_SIZE, KEY_SIZE);
    key.num = m_currentKey;
    key.isActive = true;
    key.isLooted = false;

    m_keys.push_back(key);

    ++m_currentKey;
  }

  void ItemManager::addDoor(sf::Vector2i pos, bool isVertical) {
    Door door;

    switch (m_currentDoor) {
    case 0:
      if (isVertical) {
        door.texture = m_ironDoorVerticalTexture;
      } else { // To @jube
        door.texture = m_ironDoorHorizontalTexture;
      }
      break;

    case 1:
      if (isVertical) {
        door.texture = m_bronzeDoorVerticalTexture;
      } else { // To @jube
        door.texture = m_bronzeDoorHorizontalTexture;
      }
      break;

    case 2:
      if (isVertical) {
        door.texture = m_silverDoorVerticalTexture;
      } else { // To @jube
        door.texture = m_silverDoorHorizontalTexture;
      }
      break;

    case 3:
      if (isVertical) {
        door.texture = m_goldDoorVerticalTexture;
      } else { // To @jube
        door.texture = m_goldDoorHorizontalTexture;
      }
      break;

    default:
      assert(false);
    }

    door.pos = sf::Vector2f(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
    if (isVertical) {
      door.hitbox = sf::FloatRect(pos.x * TILE_SIZE, pos.y * TILE_SIZE, DOOR_VERTICAL_SIZE_X, DOOR_VERTICAL_SIZE_Y);
    } else {
      door.hitbox = sf::FloatRect(pos.x * TILE_SIZE, pos.y * TILE_SIZE, DOOR_HORIZONTAL_SIZE_X, DOOR_HORIZONTAL_SIZE_Y);
    }
    door.num = m_currentDoor;
    door.keyFound = false;
    door.isOpen = false;
    door.isVertical = isVertical;

    m_doors.push_back(door);

    ++m_currentDoor;
  }

  void ItemManager::addRune(sf::Vector2i pos) {
    Rune rune;

    switch (m_currentRune) {
    case 0:
      rune.texture = m_rune0Texture;
      break;

    case 1:
      rune.texture = m_rune1Texture;
      break;

    case 2:
      rune.texture = m_rune2Texture;
      break;

    case 3:
      rune.texture = m_rune3Texture;
      break;

    default:
      assert(false);
    }

    rune.pos = sf::Vector2f(pos.x * TILE_SIZE + TILE_SIZE / 2, pos.y * TILE_SIZE + TILE_SIZE / 2);
    rune.hitbox = sf::FloatRect(
      pos.x * TILE_SIZE + TILE_SIZE / 2 - RUNE_SIZE / 2,
      pos.y * TILE_SIZE + TILE_SIZE / 2 - RUNE_SIZE / 2,
      RUNE_SIZE, RUNE_SIZE);

    rune.num = m_currentRune;
    rune.isActive = false;
    rune.isPressed = false;

    m_runes.push_back(rune);

    ++m_currentRune;
  }

  static sf::Vector2f center(const sf::FloatRect& rect) {
    return { rect.left + rect.width / 2, rect.top + rect.height / 2 };
  }

  game::EventStatus ItemManager::onHeroPositionEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<HeroPositionEvent *>(event);
    
    // Collisions with keys
    for (Key& key : m_keys) {
      if (!key.isActive) {
        continue;
      }

      sf::FloatRect hitboxHero = Hero::hitboxFromPosition(positionEvent->pos);
      if (hitboxHero.intersects(key.hitbox)) {
        key.isLooted = true;
      }
    }

    // Collisions with doors
    for (Door& door : m_doors) {
      if (door.isOpen /*|| door.keyFound*/) {
        continue;
      }

      auto hitboxHero = Hero::hitboxFromPosition(positionEvent->pos);
      sf::FloatRect hitboxDoor = door.hitbox;

      sf::FloatRect inter;

      if (hitboxDoor.intersects(hitboxHero, inter)) {

        sf::Vector2f n = center(hitboxDoor) - center(hitboxHero);

        float door_extent = hitboxDoor.width / 2.0f;
        float hero_extent = hitboxHero.width / 2.0f;

        float x_overlap = door_extent + hero_extent - std::abs(n.x);

        if (x_overlap <= 0) {
          continue;
        }

        door_extent = hitboxDoor.height / 2.0f;
        hero_extent = hitboxHero.height / 2.0f;
        
        float y_overlap = door_extent + hero_extent - std::abs(n.y);

        if (y_overlap <= 0) {
          continue;
        }
        
        if (door.keyFound) {
          door.isOpen = true;
          
          // TODO music
          DoorOpeningEvent event;
          gEventManager().triggerEvent(&event);          
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

    // Collisions with runes
    for (Rune& rune : m_runes) {
      if (rune.isActive) {
        continue;
      }

      sf::FloatRect hitboxHero = Hero::hitboxFromPosition(positionEvent->pos);

      if (hitboxHero.intersects(rune.hitbox)) {
        rune.isPressed = true;
      }
    }

    // Collisions with the portals
    if (m_currentPortal == 2) {
      int collisions = 0;

      for (Portal& portal : m_portals) {
        sf::FloatRect hitboxHero = Hero::hitboxFromPosition(positionEvent->pos);

        if (hitboxHero.intersects(portal.hitbox)) {
          collisions++;

          if (!m_isOnPortal) {
            positionEvent->pos = m_portals[1 - portal.num].pos;
            positionEvent->pos.y -= TILE_SIZE / 4 + TILE_SIZE / 12; // HACK
            m_isOnPortal = true;
          }
        }
      }

      if (collisions == 0) {
        m_isOnPortal = false;
      }
    }

    return game::EventStatus::KEEP;
  }

  game::EventStatus ItemManager::onKeyLootEvent(game::EventType type, game::Event *event) {
    auto positionEvent = static_cast<KeyLootEvent *>(event);

    Door &door = m_doors[positionEvent->keyNum];
    door.keyFound = true;

    return game::EventStatus::KEEP;
  }

  game::EventStatus ItemManager::onResetLevelEvent(game::EventType type, game::Event *event) {
    for (Key& key : m_keys) {
      key.isActive = true;
      key.isLooted = false;
    }

    for (Door& door : m_doors) {
      door.keyFound = false;
      door.isOpen = false;
    }

    clearRunes();

    m_portals.clear();
    m_currentPortal = 0;

    return game::EventStatus::KEEP;
  }

  game::EventStatus ItemManager::onPortalDropEvent(game::EventType type, game::Event *event) {
    if (m_currentPortal == 2) {
      return game::EventStatus::KEEP;
    }

    auto portalDrop = static_cast<PortalDropEvent*>(event);

    Portal portal;
    portal.texture = m_portalTexture;
    portal.pos = portalDrop->pos;
    portal.hitbox = sf::FloatRect(
      portal.pos.x - PORTAL_SIZE / 2,
      portal.pos.y - PORTAL_SIZE / 2,
      PORTAL_SIZE, PORTAL_SIZE
    );
    portal.num = m_currentPortal;

    m_portals.push_back(portal);

    m_currentPortal++;
    m_isOnPortal = true;

    return game::EventStatus::KEEP;
  }

  void ItemManager::update(float dt) {
    // Update keys
    for (Key& key : m_keys) {
      if (key.isLooted && key.isActive) {
        key.isActive = false;

        {
          KeyLootEvent event;
          event.keyNum = key.num;

          gEventManager().triggerEvent(&event);
        }
      }
    }

    // Update keys
    for (Rune& rune : m_runes) {
      if (rune.isPressed) {
        rune.isPressed = false;

        if (m_runeOrder[m_currentOrder] == static_cast<int>(rune.num)) {
          rune.isActive = true;
          RunePressedEvent event;
          event.runeNum = rune.num;

          gEventManager().triggerEvent(&event);
          ++m_currentOrder;
        }
        else {

          clearRunes();
        }
      }
    }
  }

  void ItemManager::render(sf::RenderWindow& window) {
    // Render the keys
    for (Key& key : m_keys) {
      if (!key.isActive) {
        continue;
      }

      sf::Sprite sprite;
      sprite.setOrigin(KEY_TEXTURE_SIZE / 2, KEY_TEXTURE_SIZE / 2);
      sprite.setScale(KEY_SIZE / KEY_TEXTURE_SIZE, KEY_SIZE / KEY_TEXTURE_SIZE);

      sprite.setTexture(*key.texture);
      sprite.setPosition(key.pos);

      window.draw(sprite);
    }

    // Render the doors
    for (Door& door : m_doors) {
      if (door.isOpen) {
        continue;
      }

      sf::Vector2f shift(0.0f, 0.0f);

      sf::Sprite sprite;
      if (door.isVertical) {
        sprite.setScale(DOOR_VERTICAL_SIZE_X / DOOR_VERTICAL_TEXTURE_SIZE_X, DOOR_VERTICAL_SIZE_Y / DOOR_VERTICAL_TEXTURE_SIZE_Y);
        shift = sf::Vector2f(0.0f, -TILE_SIZE / 2);
      } else { // To @jube
        sprite.setScale(DOOR_HORIZONTAL_SIZE_X / DOOR_HORIZONTAL_TEXTURE_SIZE_X, DOOR_HORIZONTAL_SIZE_Y / DOOR_HORIZONTAL_TEXTURE_SIZE_Y);
      }

      sprite.setTexture(*door.texture);
      sprite.setPosition(door.pos + shift);

      window.draw(sprite);
    }

    // Render the runes
    for (Rune& rune : m_runes) {
      sf::Sprite sprite;
      sprite.setOrigin(RUNE_TEXTURE_SIZE / 2, RUNE_TEXTURE_SIZE / 2);
      sprite.setScale(RUNE_SIZE / RUNE_TEXTURE_SIZE, RUNE_SIZE / RUNE_TEXTURE_SIZE);
      sprite.setTexture(*rune.texture);
      sprite.setPosition(rune.pos);

      if (rune.isActive) {
        sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, 0x80));
      }

      window.draw(sprite);
    }

    // Render the portals
    for (Portal& portal : m_portals) {
      sf::Sprite sprite;
      sprite.setOrigin(PORTAL_TEXTURE_SIZE / 2, PORTAL_TEXTURE_SIZE / 2);
      sprite.setScale(PORTAL_SIZE / PORTAL_TEXTURE_SIZE, PORTAL_SIZE / PORTAL_TEXTURE_SIZE);
      sprite.setTexture(*portal.texture);
      sprite.setPosition(portal.pos);

      window.draw(sprite);
    }
  }

  void ItemManager::clearRunes() {
    m_currentOrder = 0;
    for (Rune &rune : m_runes) {
      rune.isActive = false;
      rune.isPressed = false;
    }

    {
      FailSequenceEvent event;

      gEventManager().triggerEvent(&event);
    }
  }

}

