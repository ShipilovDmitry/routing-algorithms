#include "dijkstra.hpp"
#include "redblobgames/grids.hpp"
#include "redblobgames/utils.hpp"
#include <unordered_set>

redblobgames::GridWithWeights make_diagram4() {
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

namespace redblobgames::dijkstra {

void example_1() {
  GridWithWeights grid = make_diagram4();
  GridLocation start{1, 4}, goal{8, 3};
  std::unordered_map<GridLocation, GridLocation> cameFrom;
  std::unordered_map<GridLocation, double> costSoFar;
  dijkstraSearch(grid, start, goal, cameFrom, costSoFar);
  redblobgames::drawGrid(grid, nullptr, &cameFrom, nullptr, &start, &goal);
  std::cout << '\n';
  std::vector<GridLocation> path = reconstructPath(start, goal, cameFrom);
  redblobgames::drawGrid(grid, nullptr, nullptr, &path, &start, &goal);
}

} // namespace redblobgames::dijkstra
