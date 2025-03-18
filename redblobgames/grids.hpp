#pragma once

#include "grid_location.hpp"

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

namespace redblobgames {

struct SimpleGraph {
  using Node = char;
  using AdjacencyList = std::vector<Node>;
  std::unordered_map<Node, AdjacencyList>
      edges; // e.g., 'A' corresponds to ['B', 'C', 'D'] (adjacency list)

  std::vector<Node> neighbors(Node id) const { return edges.at(id); }
};

class SquareGrid {
public:
  SquareGrid(int width, int height) : m_width(width), m_height(height) {}

  bool inBounds(GridLocation const &id) const {
    return 0 <= id.x && id.x < m_width && 0 <= id.y && id.y < m_height;
  }

  bool passable(GridLocation const &id) const {
    return m_walls.find(id) == m_walls.end();
  }

  std::vector<GridLocation> neighbors(GridLocation const &id) const {
    std::vector<GridLocation> results;

    for (auto const &dir : kDirs) {
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (inBounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      std::reverse(results.begin(), results.end());
    }

    return results;
  }

  void addWall(int x1, int y1, int x2, int y2) {
    for (int x = x1; x < x2; ++x) {
      for (int y = y1; y < y2; ++y) {
        m_walls.insert(GridLocation{x, y});
      }
    }
  }

  bool insideWall(GridLocation const &id) const {
    return m_walls.find(id) != m_walls.end();
  }

  int width() const { return m_width; }

  int height() const { return m_height; }

private:
  static constexpr std::array<redblobgames::GridLocation, 4> kDirs{
      /* East, West, North, South */
      GridLocation{1, 0}, GridLocation{-1, 0}, GridLocation{0, -1},
      GridLocation{0, 1}};

  int m_width, m_height;
  std::unordered_set<GridLocation> m_walls;
};

class GridWithWeights : public SquareGrid {
public:
  GridWithWeights(int w, int h) : SquareGrid(w, h) {}
  double cost(GridLocation from_node, GridLocation to_node) const {
    return m_forests.find(to_node) != m_forests.end()
               ? 5
               : 1; // Forest costs more than regular road
  }

  std::unordered_set<GridLocation> m_forests;
};

} // namespace redblobgames
