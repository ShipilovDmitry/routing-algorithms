#pragma once

#include "redblobgames/utils.hpp"

namespace redblobgames::astar {

void example();

inline double heuristic(GridLocation a, GridLocation b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template <typename Location, typename Graph>
void aStarSearch(Graph const &graph, Location const &start,
                 Location const &goal,
                 std::unordered_map<Location, Location> &cameFrom,
                 std::unordered_map<Location, double> &costSoFar) {
  PriorityQueue<Location, double> frontier;
  frontier.put(start, 0);

  cameFrom[start] = start;
  costSoFar[start] = 0;

  while (!frontier.empty()) {
    Location current = frontier.get();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) {
      double new_cost = costSoFar[current] + graph.cost(current, next);
      if (costSoFar.find(next) == costSoFar.end() ||
          new_cost < costSoFar[next]) {
        costSoFar[next] = new_cost;
        double priority = new_cost + heuristic(next, goal);
        frontier.put(next, priority);
        cameFrom[next] = current;
      }
    }
  }
}

} // namespace redblobgames::astar
