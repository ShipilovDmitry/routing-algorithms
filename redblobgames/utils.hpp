#pragma once

#include "grids.hpp"
#include <iomanip>
#include <unordered_map>
#include <queue>

namespace redblobgames {

template <typename T, typename priority_t> struct PriorityQueue {
public:
  bool empty() const { return m_elements.empty(); }

  void put(T item, priority_t priority) {
    m_elements.emplace(priority, std::move(item));
  }

  T get() {
    T bestItem = m_elements.top().second;
    m_elements.pop();
    return std::move(bestItem);
  }

private:
  using PQElement = std::pair<priority_t, T>;
  std::priority_queue<PQElement, std::vector<PQElement>,
                      std::greater<PQElement>> // Greater priority is on the top
                                               // (means less cost)
      m_elements;
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

template <typename Location>
std::vector<Location>
reconstructPath(Location const &start, Location const &goal,
                std::unordered_map<Location, Location> const &came_from) {
  std::vector<Location> path;
  Location current = goal;
  if (came_from.find(goal) == came_from.end()) {
    return path; // no path can be found
  }
  while (current != start) {
    path.push_back(current);
    current = came_from.at(current);
  }
  path.push_back(start);                  // optional
  std::reverse(path.begin(), path.end()); // optional
  return path;
}

inline redblobgames::GridWithWeights make_diagram4() {
  redblobgames::GridWithWeights grid(10, 10);
  grid.addWall(1, 7, 4, 9);
  using L = redblobgames::GridLocation;
  grid.m_forests = std::unordered_set<L>{
      L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2}, L{4, 3}, L{4, 4}, L{4, 5},
      L{4, 6}, L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2}, L{5, 3}, L{5, 4},
      L{5, 5}, L{5, 6}, L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3}, L{6, 4},
      L{6, 5}, L{6, 6}, L{6, 7}, L{7, 3}, L{7, 4}, L{7, 5}};
  return grid;
}

} // namespace redblobgames
