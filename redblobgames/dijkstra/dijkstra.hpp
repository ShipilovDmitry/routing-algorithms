#pragma once

#include "redblobgames/utils.hpp"
#include <vector>

namespace redblobgames::dijkstra {

template <typename Location, typename Graph>
void dijkstraSearch(Graph const &graph, Location const &start,
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
      double const newCost = costSoFar[current] + graph.cost(current, next);
      if (costSoFar.find(next) == costSoFar.end() ||
          newCost < costSoFar[next]) {
        costSoFar[next] = newCost;
        cameFrom[next] = current;
        frontier.put(next, newCost);
      }
    }
  }
}



void example_1();

} // namespace redblobgames::dijkstra
