#pragma once

#include <queue>
#include <unordered_map>

namespace bfs {

void example_1();
void example_2();
void example_3();

template <typename Location, typename Graph>
std::unordered_map<Location, Location>
breadth_first_search(Graph const &graph, Location const &start) {
  std::queue<Location> frontier;
  frontier.push(start);

  std::unordered_map<Location, Location> cameFrom;
  cameFrom[start] = start;

  while (!frontier.empty()) {
    Location const current = frontier.front();
    frontier.pop();

    for (Location next : graph.neighbors(current)) {
      if (cameFrom.find(next) == cameFrom.end()) {
        frontier.push(next);
        cameFrom[next] = current;
      }
    }
  }
  return cameFrom;
}

template <typename Location, typename Graph>
std::unordered_map<Location, Location>
breadth_first_search(Graph const &graph, Location const &start,
                     Location const &goal) {
  std::queue<Location> frontier;
  frontier.push(start);

  std::unordered_map<Location, Location> cameFrom;
  cameFrom[start] = start;

  while (!frontier.empty()) {
    Location current = frontier.front();
    frontier.pop();

    if (current == goal) {
      break;
    }

    for (Location next : graph.neighbors(current)) {
      if (cameFrom.find(next) == cameFrom.end()) {
        frontier.push(next);
        cameFrom[next] = current;
      }
    }
  }
  return cameFrom;
}

} // namespace bfs
