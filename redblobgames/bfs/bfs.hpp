#pragma once
#include "redblobgames/grids.hpp"

namespace bfs {

using Node = redblobgames::SimpleGraph::Node;
void breadthFirstSearch(redblobgames::SimpleGraph const &graph, Node const &start);
void example();
} // namespace bfs
