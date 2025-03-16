#pragma once

#include <queue>
#include <vector>

namespace redblobgames::dijkstra {

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
                      std::greater<PQElement>> // Greater priority is on the top (means less cost)
      m_elements;
};

template <typename Location, typename Graph>
void dijkstra_search(Graph const &graph, Location const &start,
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

template <typename Location>
std::vector<Location>
reconstruct_path(Location const &start, Location const &goal,
                 std::unordered_map<Location, Location> came_from) {
  std::vector<Location> path;
  Location current = goal;
  if (came_from.find(goal) == came_from.end()) {
    return path; // no path can be found
  }
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}

void example_1();

} // namespace redblobgames::dijkstra
