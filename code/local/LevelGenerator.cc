#include "LevelGenerator.h"

#include <cassert>
#include <iostream>

namespace huaca {

  void LevelGenerator::generateFirst() {
    static constexpr int MIN = SIZE / 3;
    static constexpr int MAX = 2 * SIZE / 3;

    for (unsigned int i = 0; i < SIZE; ++i) {
      for (unsigned int j = 0; j < SIZE; ++j) {
        Cell cell;

        if (i < MIN || i > MAX || j < MIN || j > MAX) {
          cell.type = CellType::WALL;
        } else {
          cell.type = CellType::GROUND;
        }

        cell.tile = 0;
        m_ground[i][j] = cell;
      }
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
