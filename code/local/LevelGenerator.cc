#include "LevelGenerator.h"

#include <iostream>

#include "Singletons.h"

namespace huaca {

  void LevelGenerator::generateFirst() {
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
      Cell cell;

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[i][2 + SHIFT] = cell;

      //Couloir 5

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[i][10 + SHIFT] = cell;
    }
    //Couloir 2
    for (unsigned int i = 17 + SHIFT; i < 20 + SHIFT; ++i) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][2 + SHIFT] = cell;

      //Couloir 6

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][10 + SHIFT] = cell;
    }

    //Couloir 3
    for (unsigned int j = 5 + SHIFT; j < 8 + SHIFT; ++j) {
      Cell cell;

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[3 + SHIFT][j] = cell;

      //Couloir 4

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[23 + SHIFT][j] = cell;
    }

    {
      std::cout << "ici" << std::endl;
      NewLevelEvent event;
      event.posHero = {0.0f, 0.0f};

      gEventManager().triggerEvent(&event);
    }
  }

  void LevelGenerator::generateNew(game::Random& random) {
    for (std::size_t i = 0; i < SIZE; ++i) {
      for (std::size_t j = 0; j < SIZE; ++j) {
        m_ground[i][j].type = CellType::WALL;
      }
    }

    generateRooms(random, 0, SIZE, 0, SIZE);

    for (std::size_t i = 0; i < SIZE; ++i) {
      for (std::size_t j = 0; j < SIZE; ++j) {
        if (m_ground[i][j].type == CellType::WALL) {
          std::cout << '#';
        } else {
          std::cout << ' ';
        }
      }

      std::cout << '\n';
    }
  }

  static constexpr std::size_t SIZE_MIN = 12;
  static constexpr std::size_t SIZE_PAD = 5;

  void LevelGenerator::generateRooms(game::Random& random, std::size_t iMin, std::size_t iMax, std::size_t jMin, std::size_t jMax) {
    std::size_t iLength = iMax - iMin;
    std::size_t jLength = jMax - jMin;

    if (iLength < SIZE_MIN && jLength < SIZE_MIN) {
      assert(iLength >= 5);
      assert(jLength >= 5);

//       std::cout << iLength << 'x' << jLength << '\n';

      int height = random.computeUniformInteger(3, iLength - 2);
      int width = random.computeUniformInteger(3, jLength - 2);

      int iStart = random.computeUniformInteger(iMin + 1, iMax - height - 1);
      int jStart = random.computeUniformInteger(jMin + 1, jMax - width - 1);

      for (int i = iStart; i < iStart + height; ++i) {
        for (int j = jStart; j < jStart + width; ++j) {
          m_ground[i][j].type = CellType::GROUND;
        }
      }

      return;
    }

    enum { HORIZONTAL, VERTICAL } split = HORIZONTAL;

    if (iLength < SIZE_MIN) {
      split = VERTICAL;
    } else if (jLength < SIZE_MIN) {
      split = HORIZONTAL;
    } else {
      split = random.computeBernoulli(0.5f) ? HORIZONTAL : VERTICAL;
    }

    if (split == VERTICAL) {
      std::size_t jMid = random.computeUniformInteger(jMin + SIZE_PAD, jMax - SIZE_PAD);
      generateRooms(random, iMin, iMax, jMin, jMid);
      generateRooms(random, iMin, iMax, jMid, jMax);

      std::size_t iMid = iMin + (iMax - iMin) / 2;

      std::size_t j = jMid;

      while (j < jMax) {
        if (m_ground[iMid][j].type == CellType::GROUND) {
          break;
        }

        m_ground[iMid][j].type = CellType::GROUND;
        j++;
      }

      j = jMid - 1;

      while (j > jMin) {
        if (m_ground[iMid][j].type == CellType::GROUND) {
          break;
        }

        m_ground[iMid][j].type = CellType::GROUND;
        j--;
      }

    } else {
      std::size_t iMid = random.computeUniformInteger(iMin + SIZE_PAD, iMax - SIZE_PAD);
      generateRooms(random, iMin, iMid, jMin, jMax);
      generateRooms(random, iMid, iMax, jMin, jMax);

      std::size_t jMid = jMin + (jMax - jMin) / 2;

      std::size_t i = iMid;

      while (i < iMax) {
        if (m_ground[i][jMid].type == CellType::GROUND) {
          break;
        }

        m_ground[i][jMid].type = CellType::GROUND;
        i++;
      }

      i = iMid - 1;

      while (i > iMin + 1) {
        if (m_ground[i][jMid].type == CellType::GROUND) {
          break;
        }

        m_ground[i][jMid].type = CellType::GROUND;
        i--;
      }

    }

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
