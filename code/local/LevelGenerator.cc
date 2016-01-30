#include "LevelGenerator.h"

#include <cassert>
#include <iostream>

namespace huaca {

  void LevelGenerator::generateFirst() {
    // Fill with a wall
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
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
    for (int i = 0 + SHIFT; i < 7 + SHIFT; ++i) {
      for (int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 4
      for (int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Salle 2
    for (int i = 10 + SHIFT; i < 17 + SHIFT; ++i) {
      for (int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 5
      for (int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Salle 3
    for (int i = 20 + SHIFT; i < 27 + SHIFT; ++i) {
      for (int j = 8 + SHIFT; j < 13 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
      //Salle 6
      for (int j = 0 + SHIFT; j < 5 + SHIFT; ++j) {
        Cell cell;

        cell.type = CellType::GROUND;
        cell.tile = 1;
        m_ground[i][j] = cell;
      }
    }

    //Couloir 1
    for (int i = 7 + SHIFT; i < 10 + SHIFT; ++i) {
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
    for (int i = 17 + SHIFT; i < 20 + SHIFT; ++i) {
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
    for (int j = 5 + SHIFT; j < 8 + SHIFT; ++j) {
      Cell cell;

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[3 + SHIFT][j] = cell;

      //Couloir 4

      cell.type = CellType::GROUND;
      cell.tile = 1;
      m_ground[23 + SHIFT][j] = cell;
    }

    /*{
      HeroPositionEvent event;
      event.pos = m_pos;

      gEventManager().triggerEvent(&event);

      m_pos = event.pos;
    }*/
  }

  void LevelGenerator::generateNew(game::Random& random) {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        m_ground[i][j].type = CellType::WALL;
        m_ground[i][j].tile = -1;
        m_ground[i][j].color = Cell::WHITE;
      }
    }

    generateRooms(random, 0, SIZE, 0, SIZE);

    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        if (m_ground[i][j].type == CellType::WALL) {
          std::cout << '#';
        } else {
          std::cout << ' ';
        }
      }

      std::cout << '\n';
    }

    generateItems(random);
  }

  static constexpr int SIZE_MIN = 12;
  static constexpr int SIZE_PAD = 5;

  void LevelGenerator::generateRooms(game::Random& random, int iMin, int iMax, int jMin, int jMax) {
    int iLength = iMax - iMin;
    int jLength = jMax - jMin;

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
      int jMid = random.computeUniformInteger(jMin + SIZE_PAD, jMax - SIZE_PAD);
      generateRooms(random, iMin, iMax, jMin, jMid);
      generateRooms(random, iMin, iMax, jMid, jMax);

      int iMid = iMin + (iMax - iMin) / 2;

      int j = jMid;

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
      int iMid = random.computeUniformInteger(iMin + SIZE_PAD, iMax - SIZE_PAD);
      generateRooms(random, iMin, iMid, jMin, jMax);
      generateRooms(random, iMid, iMax, jMin, jMax);

      int jMid = jMin + (jMax - jMin) / 2;

      int i = iMid;

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

  void LevelGenerator::generateItems(game::Random& random) {
    m_rune0Pos = m_rune1Pos = m_rune2Pos = m_rune3Pos = sf::Vector2i(0, 0);

    int x, y;

    // rune 0
    do {
      x = random.computeUniformInteger(0, SIZE - 1);
      y = random.computeUniformInteger(0, SIZE - 1);
    } while (m_ground[y][x].type != CellType::GROUND || collidesWithRunes(x, y));

    m_rune0Pos = sf::Vector2i(x, y);

    // rune 1
    do {
      x = random.computeUniformInteger(0, SIZE - 1);
      y = random.computeUniformInteger(0, SIZE - 1);
    } while (m_ground[y][x].type != CellType::GROUND || collidesWithRunes(x, y));

    m_rune1Pos = sf::Vector2i(x, y);

    // rune 2
    do {
      x = random.computeUniformInteger(0, SIZE - 1);
      y = random.computeUniformInteger(0, SIZE - 1);
    } while (m_ground[y][x].type != CellType::GROUND || collidesWithRunes(x, y));

    m_rune2Pos = sf::Vector2i(x, y);

    // rune 3
    do {
      x = random.computeUniformInteger(0, SIZE - 1);
      y = random.computeUniformInteger(0, SIZE - 1);
    } while (m_ground[y][x].type != CellType::GROUND || collidesWithRunes(x, y));

    m_rune3Pos = sf::Vector2i(x, y);

    std::cout << "Rune 0: " << m_rune0Pos.x << ',' << m_rune0Pos.y << '\n';
    std::cout << "Rune 1: " << m_rune1Pos.x << ',' << m_rune1Pos.y << '\n';
    std::cout << "Rune 2: " << m_rune2Pos.x << ',' << m_rune2Pos.y << '\n';
    std::cout << "Rune 3: " << m_rune3Pos.x << ',' << m_rune3Pos.y << '\n';


    // hero
    do {
      x = random.computeUniformInteger(0, SIZE - 1);
      y = random.computeUniformInteger(0, SIZE - 1);
    } while (m_ground[y][x].type != CellType::GROUND || collidesWithRunes(x, y));

    m_heroPos = sf::Vector2i(x, y);

    std::cout << "Hero: " << m_heroPos.x << ',' << m_heroPos.y << '\n';

    // DFS
    std::vector<sf::Vector2i> stack;
    m_ground[m_heroPos.y][m_heroPos.x].color = Cell::GREY;
    stack.push_back(m_heroPos);

    std::vector<sf::Vector2i> path;

//     do {
//
//
//     } while (!stack.empty());


  }

  bool LevelGenerator::collidesWithRunes(int x, int y) {
    sf::Vector2i curr(x, y);

    if (curr == m_rune0Pos) {
      return true;
    }

    if (curr == m_rune1Pos) {
      return true;
    }

    if (curr == m_rune2Pos) {
      return true;
    }

    if (curr == m_rune3Pos) {
      return true;
    }

    return false;
  }

  GroundManager LevelGenerator::getGroundManager() const {
    GroundManager manager;

    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
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

    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        Cell cell = m_ground[i][j];

        if (cell.type == CellType::WALL) {
          manager.addWall(sf::Vector2f(i, j), cell.tile);
        }
      }
    }

    return manager;
  }


}
