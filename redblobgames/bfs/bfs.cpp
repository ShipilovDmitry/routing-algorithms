#include "bfs.hpp"

namespace bfs {

void breadthFirstSearch(redblobgames::SimpleGraph const &graph,
                        Node const &start) {
  std::queue<Node> frontier;
  frontier.push(start);

  std::unordered_set<Node> reached;
  reached.insert(start);

  while (!frontier.empty()) {
    auto current = frontier.front();
    frontier.pop();

    std::cout << "  Visiting " << current << '\n';
    for (auto next : graph.neighbors(current)) {
      if (reached.find(next) == reached.end()) {
        frontier.push(next);
        reached.insert(next);
      }
    }
  }
}

void example() {
  redblobgames::SimpleGraph const example_graph{{
      {'A', {'B'}},
      {'B', {'C'}},
      {'C', {'B', 'D', 'F'}},
      {'D', {'C', 'E'}},
      {'E', {'F'}},
      {'F', {}},
  }};

  std::cout << "Reachable from A:\n";
  breadthFirstSearch(example_graph, 'A');
  std::cout << "Reachable from E:\n";
  breadthFirstSearch(example_graph, 'E');
}
} // namespace bfs
