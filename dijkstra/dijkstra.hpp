#pragma once

#include <cstdint>
#include <vector>
#include <cstddef>

namespace dijkstra {

struct Node {
  size_t id;       // id in adjacency list: 0, 1, 2, 3, etc..
  uint32_t weight; // cost to go to the id from startNode
};

using AdjacencyList =
    std::vector<Node>; // Each column is a node that has several nodes to go to
using Graph = std::vector<AdjacencyList>;

std::vector<uint32_t> shortestPaths(Graph const &graph, size_t startNode);

void example();
} // namespace dijkstra
