#include "LevelGenerator.h"

#include <iostream>

#include "Constants.h"
#include "Hero.h"
#include "Singletons.h"

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

    // Set key 
    m_key0Pos = {SHIFT + 6, SHIFT + 3};
    m_key1Pos = {SHIFT + 5, SHIFT + 3};
    m_key2Pos = {SHIFT + 5, SHIFT + 2};
    m_key3Pos = {SHIFT + 6, SHIFT + 2};

    // Set door 
    m_door0Pos = {SHIFT + 1, SHIFT + 3};
    m_door1Pos = {SHIFT + 2, SHIFT + 3};
    m_door2Pos = {SHIFT + 2, SHIFT + 2};
    m_door3Pos = {SHIFT + 1, SHIFT + 2};
    m_door0Vertical = true;
    m_door1Vertical = true;
    m_door2Vertical = true;
    m_door3Vertical = true;

    // Set runes
    m_rune0Pos = {SHIFT + 1, SHIFT + 0};
    m_rune1Pos = {SHIFT + 2, SHIFT + 0};
    m_rune2Pos = {SHIFT + 3, SHIFT + 0};
    m_rune3Pos = {SHIFT + 4, SHIFT + 0};

    // Set the hero position
    {
      NewLevelEvent event;

      sf::Vector2f spriteCenter((SHIFT + 3.5) * TILE_SIZE, (SHIFT + 2.5) * TILE_SIZE);
      sf::FloatRect rect = Hero::hitboxFromPosition(spriteCenter);

      sf::Vector2f hitboxCenter(rect.left + (rect.width / 2.0f), rect.top - (rect.height / 2.0f));

      event.posHero = hitboxCenter;

      gEventManager().triggerEvent(&event);
    }
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
    generateItems(random);

    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        if (m_ground[i][j].type == CellType::WALL) {
          std::cout << '#';
        } else {
          sf::Vector2i curr(j, i);

          if (curr == m_heroPos) {
            std::cout << '@';
          } else if (curr == m_rune0Pos) {
            std::cout << '0';
          } else if (curr == m_rune1Pos) {
            std::cout << '1';
          } else if (curr == m_rune2Pos) {
            std::cout << '2';
          } else if (curr == m_rune3Pos) {
            std::cout << '3';
          } else if (curr == m_key0Pos) {
            std::cout << 'a';
          } else if (curr == m_key1Pos) {
            std::cout << 'b';
          } else if (curr == m_key2Pos) {
            std::cout << 'c';
          } else if (curr == m_key3Pos) {
            std::cout << 'd';
          } else if (curr == m_door0Pos) {
            std::cout << 'A';
          } else if (curr == m_door1Pos) {
            std::cout << 'B';
          } else if (curr == m_door2Pos) {
            std::cout << 'C';
          } else if (curr == m_door3Pos) {
            std::cout << 'D';
          } else {
            std::cout << ' ';
          }
        }
      }

      std::cout << '\n';
    }

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

    sf::Vector2i dirs[4] = {
      {  0,  1 },
      {  0, -1 },
      {  1,  0 },
      { -1,  0 },
    };

    do {
      sf::Vector2i curr = stack.back();
      Cell& currCell = m_ground[curr.y][curr.x];
      assert(currCell.color == Cell::GREY);
      currCell.color = Cell::BLACK;
      stack.pop_back();
      path.push_back(curr);

      for (int k = 0; k < 10; ++k) {
        int i = random.computeUniformInteger(0, 3);
        int j = random.computeUniformInteger(0, 3);
        std::swap(dirs[i], dirs[j]);
      }

      for (int k = 0; k < 4; ++k) {
        sf::Vector2i next = curr + dirs[k];

        Cell& nextCell = m_ground[next.y][next.x];

        if (nextCell.type == CellType::GROUND && nextCell.color == Cell::WHITE) {
          nextCell.color = Cell::GREY;
          stack.push_back(next);
        }
      }

    } while (!stack.empty());

    m_key0Pos  = m_key1Pos  = m_key2Pos  = m_key3Pos  = sf::Vector2i(0, 0);
    m_door0Pos = m_door1Pos = m_door2Pos = m_door3Pos = sf::Vector2i(0, 0);

    std::cout << "path length: " << path.size() << '\n';

    int keyIndexMin = path.size() / 4;
    int keyIndexMax = 3 * path.size() / 4;

    int index;

    // key 0
    do {
      index = random.computeUniformInteger(keyIndexMin, keyIndexMax);
    } while (collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index]));

    m_key0Pos = path[index];

    // door0
    m_door0Pos = getDoor(random, index + 1, path);

//     std::cout << "key0: " << m_key0Pos.x << ',' << m_key0Pos.y << ' ' << index << '\n';
//     std::cout << "key0: " << m_key0Pos.x << ',' << m_key0Pos.y << ' ' << index << '\n';

    // key 1
    do {
      index = random.computeUniformInteger(keyIndexMin, keyIndexMax);
    } while (collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index]));

    m_key1Pos = path[index];

    // door1
    m_door1Pos = getDoor(random, index + 1, path);

    // key 2
    do {
      index = random.computeUniformInteger(keyIndexMin, keyIndexMax);
    } while (collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index]));

    m_key2Pos = path[index];

    // door2
    m_door2Pos = getDoor(random, index + 1, path);

    // key 3
    do {
      index = random.computeUniformInteger(keyIndexMin, keyIndexMax);
    } while (collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index]));

    m_key3Pos = path[index];

    // door3
    m_door3Pos = getDoor(random, index + 1, path);
  }

  sf::Vector2i LevelGenerator::getDoor(game::Random& random, int index, const std::vector<sf::Vector2i>& path) {
    int doorRange = path.size() - index;
    int doorIndexMin = index + doorRange / 3;
    int doorIndexMax = index + 2 * doorRange / 3;

    do {
      index = random.computeUniformInteger(doorIndexMin, doorIndexMax);
    } while (collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index]));

    while (!isCorridor(path[index]) || collidesWithRunes(path[index].x, path[index].y) || collidesWithKeysOrDoors(path[index])) {
      index++;
    }

    assert(static_cast<std::size_t>(index) < path.size());
    return path[index];
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

  bool LevelGenerator::collidesWithKeysOrDoors(const sf::Vector2i& pos) {
    if (pos == m_key0Pos) {
      return true;
    }

    if (pos == m_key1Pos) {
      return true;
    }

    if (pos == m_key2Pos) {
      return true;
    }

    if (pos == m_key3Pos) {
      return true;
    }

    if (pos == m_door0Pos) {
      return true;
    }

    if (pos == m_door1Pos) {
      return true;
    }

    if (pos == m_door2Pos) {
      return true;
    }

    if (pos == m_door3Pos) {
      return true;
    }

    return false;
  }

  bool LevelGenerator::isCorridor(const sf::Vector2i& pos) {
    Cell& n = m_ground[pos.y - 1][pos.x];
    Cell& s = m_ground[pos.y + 1][pos.x];
    Cell& w = m_ground[pos.y][pos.x - 1];
    Cell& e = m_ground[pos.y][pos.x + 1];

    return n.type == s.type && w.type == e.type && n.type != w.type;
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

    // Add the key
    manager.addKey(m_key0Pos);
    manager.addKey(m_key1Pos);
    manager.addKey(m_key2Pos);
    manager.addKey(m_key3Pos);

    // Add doors
    manager.addDoor(m_door0Pos, m_door0Vertical);
    manager.addDoor(m_door1Pos, m_door1Vertical);
    manager.addDoor(m_door2Pos, m_door2Vertical);
    manager.addDoor(m_door3Pos, m_door3Vertical);

    // Add runes
    manager.addRune(m_rune0Pos);
    manager.addRune(m_rune1Pos);
    manager.addRune(m_rune2Pos);
    manager.addRune(m_rune3Pos);

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
