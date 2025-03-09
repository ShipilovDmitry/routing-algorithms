#include "dijkstra.hpp"
#include <cstdint>
#include <iostream>
#include <queue>

namespace dijkstra {
struct CompareNodes {
  bool operator()(const Node &a, const Node &b) const {
    return a.weight > b.weight;
  }
};

std::vector<uint32_t> shortestPaths(Graph const &graph, size_t startNode) {
  std::vector<uint32_t> distances(
      graph.size(), UINT32_MAX); // large distances mean "not calculated yet"
  std::vector<bool> visited(graph.size(),
                            false); // was best path found for node or not

  std::priority_queue<Node, std::vector<Node>, CompareNodes>
      pq; // keep low weight near the root. we don't need std::set here
          // we need priority queue for optimization: we will not discover more
          // than one time optimized nodes

  pq.push({startNode, 0}); // it is free to go to myself
  distances[startNode] = 0;

  while (!pq.empty()) {
    // Dequeue the node with the minimum distance
    auto [currentNode, wheight] = pq.top();
    pq.pop();

    if (visited[currentNode]) { // do nothing if we already analized neighbours
                                // for this node
      continue;
    }
    visited[currentNode] = true;

    // Update the distance of neighboring nodes
    for (Node const &neighbor : graph[currentNode]) {
      if (visited[neighbor.id]) { // do nothing if we already analized
                                  // neighbours
                                  // for this neighbour
        continue;
      }

      if (distances[currentNode] + neighbor.weight >= distances[neighbor.id]) {
        // we can use equal for alternates
        continue;
      }

      distances[neighbor.id] = distances[currentNode] + neighbor.weight;
      pq.push({neighbor.id, distances[neighbor.id]});
    }
  }

  return distances;
}

void example() {
  // Define the graph as an adjacency list
  Graph graph = {{{1, 4}, {2, 2}},
                 {{0, 4}, {3, 5}, {4, 3}},
                 {{0, 2}, {4, 1}, {5, 6}},
                 {{1, 5}, {4, 2}, {6, 3}},
                 {{1, 3}, {3, 2}, {7, 2}, {8, 1}},
                 {{2, 6}, {9, 3}},
                 {{3, 3}, {10, 1}, {5, 1}},
                 {{4, 2}},
                 {{5, 1}},
                 {{6, 1}},
                 {{7, 3}}};

  size_t startVertex = 0; // Choose the starting vertex

  auto const distances = shortestPaths(graph, startVertex);

  // Print the shortest distances
  std::cout << "Vertex\tDistance from Source" << std::endl;
  for (int i = 0; i < graph.size(); ++i) {
    std::cout << i << "\t\t" << distances[i] << std::endl;
  }
}

} // namespace dijkstra
