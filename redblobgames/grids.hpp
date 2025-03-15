#pragma once

#include "grid_location.hpp"

#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace redblobgames {

struct SimpleGraph {
  using Node = char;
  using AdjacencyList = std::vector<Node>;
  std::unordered_map<Node, AdjacencyList>
      edges; // e.g., 'A' corresponds to ['B', 'C', 'D'] (adjacency list)

  std::vector<Node> neighbors(Node id) const { return edges.at(id); }
};

struct SquareGrid {
  static constexpr std::array<redblobgames::GridLocation, 4> kDirs{
      /* East, West, North, South */
      GridLocation{1, 0}, GridLocation{-1, 0}, GridLocation{0, -1},
      GridLocation{0, 1}};

  int width, height;
  std::unordered_set<GridLocation> walls;

  SquareGrid(int width_, int height_) : width(width_), height(height_) {}

  bool inBounds(GridLocation const &id) const {
    return 0 <= id.x && id.x < width && 0 <= id.y && id.y < height;
  }

  bool passable(GridLocation const &id) const {
    return walls.find(id) == walls.end();
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
};

} // namespace redblobgames
