#include "LevelGenerator.h"

namespace huaca {

  void LevelGenerator::generateFirst() {
    for (unsigned int i = 0; i < SIZE; ++i) {
      for (unsigned int j = 0; j < SIZE; ++j) {
        Cell cell;
        if (i % 2 == 0) {
          cell.type = CellType::WALL;
        }
        else {
          cell.type = CellType::GROUND;
        }
        cell.tile = 0;
        m_ground[i][j] = cell;
      }
    }
  }

  void LevelGenerator::generateNew(game::Random& random) {

  }

  GroundManager LevelGenerator::getGroundManager() const {
    GroundManager manager;

    /*for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++i) {
        Cell cell = m_ground[i][j];

        if (cell.type == GROUND) {

        }
      }
    }*/

    return manager;
  }

  ItemManager LevelGenerator::getItemManager() const {
    ItemManager manager;


    return manager;
  }

  WallManager LevelGenerator::getWallManager() const {
    WallManager manager;

    for (unsigned int i = 0; i < SIZE; ++i) {
      for (unsigned int j = 0; j < SIZE; ++j) {
        Cell cell = m_ground[i][j];

        if (cell.type == CellType::WALL) {
          manager.addWall(sf::Vector2f(i, j), cell.tile);
        }
      }
    }

    return manager;
  }


}
