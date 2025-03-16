#include "dijkstra.hpp"
#include "redblobgames/grids.hpp"
#include "redblobgames/utils.hpp"
#include <unordered_set>


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
