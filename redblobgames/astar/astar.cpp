#include "astar.hpp"
#include "redblobgames/utils.hpp"

namespace redblobgames::astar {
void example() {
  GridWithWeights grid = make_diagram4();
  GridLocation start{1, 4}, goal{8, 3};
  std::unordered_map<GridLocation, GridLocation> came_from;
  std::unordered_map<GridLocation, double> cost_so_far;
  aStarSearch(grid, start, goal, came_from, cost_so_far);
  drawGrid(grid, nullptr, &came_from, nullptr, &start, &goal);
  std::cout << '\n';
  std::vector<GridLocation> path = reconstructPath(start, goal, came_from);
  drawGrid(grid, nullptr, nullptr, &path, &start, &goal);
  std::cout << '\n';
  drawGrid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}

} // namespace redblobgames::astar
