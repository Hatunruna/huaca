#ifndef LOCAL_LEVEL_GENERATOR_H
#define LOCAL_LEVEL_GENERATOR_H

#include "game/Random.h"

#include "GroundManager.h"
#include "ItemManager.h"
#include "WallManager.h"

namespace huaca {

  class LevelGenerator {
  public:
    void generateFirst();
    void generateNew(game::Random& random);

    GroundManager getGroundManager() const;
    ItemManager getItemManager() const;
    WallManager getWallManager() const;

  private:
    static constexpr int SIZE = 40;

    enum class CellType {
      WALL,
      GROUND,
    };

    struct Cell {
      CellType type;
      int tile;
      enum { WHITE, GREY, BLACK } color;
    };

    Cell m_ground[SIZE][SIZE];

    sf::Vector2i m_heroPos;

    sf::Vector2i m_key0Pos;
    sf::Vector2i m_key1Pos;
    sf::Vector2i m_key2Pos;
    sf::Vector2i m_key3Pos;

    sf::Vector2i m_door0Pos;
    sf::Vector2i m_door1Pos;
    sf::Vector2i m_door2Pos;
    sf::Vector2i m_door3Pos;

    sf::Vector2i m_rune0Pos;
    sf::Vector2i m_rune1Pos;
    sf::Vector2i m_rune2Pos;
    sf::Vector2i m_rune3Pos;

  private:

    void generateRooms(game::Random& random, int iMin, int iMax, int jMin, int jMax);
    void generateItems(game::Random& random);

    bool collidesWithRunes(int x, int y);

  };


}

#endif // LOCAL_LEVEL_GENERATOR_H
