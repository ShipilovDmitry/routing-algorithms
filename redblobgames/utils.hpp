#pragma once
#include "grid_location.hpp"

#include <iomanip>
#include <unordered_map>

namespace redblobgames {

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
