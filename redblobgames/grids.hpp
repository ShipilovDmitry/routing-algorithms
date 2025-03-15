#pragma once

#include "grid_location.hpp"

#include <array>
#include <iomanip>
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

// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template <class Graph>
void drawGrid(
    const Graph &graph,
    std::unordered_map<GridLocation, double> *distances = nullptr,
    std::unordered_map<GridLocation, GridLocation> *point_to = nullptr,
    std::vector<GridLocation> *path = nullptr, GridLocation *start = nullptr,
    GridLocation *goal = nullptr) {
  constexpr auto fieldWidth = 3;
  std::cout << std::string(fieldWidth * graph.width(), '_') << '\n';
  for (int y = 0; y != graph.height(); ++y) {
    for (int x = 0; x != graph.width(); ++x) {
      GridLocation id{x, y};
      if (graph.insideWall(id)) {
        std::cout << std::string(fieldWidth, '#');
      } else if (start && id == *start) {
        std::cout << " A ";
      } else if (goal && id == *goal) {
        std::cout << " Z ";
      } else if (path != nullptr &&
                 find(path->begin(), path->end(), id) != path->end()) {
        std::cout << " @ ";
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) {
          std::cout << " > ";
        } else if (next.x == x - 1) {
          std::cout << " < ";
        } else if (next.y == y + 1) {
          std::cout << " v ";
        } else if (next.y == y - 1) {
          std::cout << " ^ ";
        } else {
          std::cout << " * ";
        }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << ' ' << std::left << std::setw(fieldWidth - 1)
                  << (*distances)[id];
      } else {
        std::cout << " . ";
      }
    }
    std::cout << '\n';
  }
  std::cout << std::string(fieldWidth * graph.width(), '~') << '\n';
}

} // namespace redblobgames
