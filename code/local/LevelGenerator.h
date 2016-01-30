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
    static constexpr std::size_t SIZE = 40;

    enum class CellType {
      WALL,
      GROUND,
    };

    struct Cell {
      CellType type;
      std::size_t tile;
    };

    Cell m_ground[SIZE][SIZE];
  };


}

#endif // LOCAL_LEVEL_GENERATOR_H
