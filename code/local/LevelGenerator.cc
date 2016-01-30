#include "LevelGenerator.h"

#include <cassert>

namespace huaca {

  void LevelGenerator::generateFirst() {
    static constexpr int MIN = SIZE / 3;
    static constexpr int MAX = 2 * SIZE / 3;

    // Fill with a wall
    for (unsigned int i = 0; i < SIZE; ++i) {
      for (unsigned int j = 0; j < SIZE; ++j) {
        Cell cell;

        cell.type = CellType::WALL;
        cell.tile = 0;
        m_ground[i][j] = cell;
      }
    }

    // Design the tutorial stage
    // 7 * 5 piece et 3 * 1 couloir hor et 1 * 3 vert
    
    const int SHIFT = 10;
    //Salle 1
    for (unsigned int i = 0 + SHIFT; i < 7 + SHIFT; ++i) {
      for (unsigned int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 4
      for (unsigned int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Salle 2
    for (unsigned int i = 10 + SHIFT; i < 17 + SHIFT; ++i) {
      for (unsigned int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 5
      for (unsigned int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Couloir 2
    for (unsigned int i = 7 + SHIFT; i < 10 + SHIFT; ++i) {
      for (unsigned int j = 0 + SHIFT; j < 1 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Salle 3
    for (unsigned int i = 20 + SHIFT; i < 27 + SHIFT; ++i) {
      for (unsigned int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 6
      for (unsigned int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Couloir 1
    for (unsigned int i = 7 + SHIFT; i < 10 + SHIFT; ++i) {
      for (unsigned int j = 2 + SHIFT; j < 3 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Couloir 5
      for (unsigned int j = 10 + SHIFT; j < 11 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }
    //Couloir 2
    for (unsigned int i = 17 + SHIFT; i < 20 + SHIFT; ++i) {
      for (unsigned int j = 2 + SHIFT; j < 3 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Couloir 6
      for (unsigned int j = 10 + SHIFT; j < 11 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Couloir 3
    for (unsigned int i = 3 + SHIFT; i < 4 + SHIFT; ++i) {
      for (unsigned int j = 5 + SHIFT; j < 8 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }
    //Couloir 4
    for (unsigned int i = 23 + SHIFT; i < 24 + SHIFT; ++i) {
      for (unsigned int j = 5 + SHIFT; j < 8 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }
  }

  void LevelGenerator::generateNew(game::Random& random) {

  }

  GroundManager LevelGenerator::getGroundManager() const {
    GroundManager manager;

    for (unsigned int i = 0; i < SIZE; ++i) {
      for (unsigned int j = 0; j < SIZE; ++j) {
        Cell cell = m_ground[i][j];

        switch (cell.type) {
        case CellType::GROUND:
          manager.addGround(sf::Vector2f(i, j), cell.tile);
          break;

        case CellType::WALL:
          manager.addHalfWall(sf::Vector2f(i, j), cell.tile);
          break;

        default:
          assert(false);
        }
      }
    }

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
