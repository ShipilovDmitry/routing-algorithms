#include "bfs.hpp"

#include "redblobgames/grids.hpp"
#include "redblobgames/utils.hpp"

using namespace redblobgames;

namespace bfs {
using Node = SimpleGraph::Node;

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

void example_1() {
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

SquareGrid makeDiagram1() {
  SquareGrid grid(30, 15);
  grid.addWall(3, 3, 5, 12);
  grid.addWall(13, 4, 15, 15);
  grid.addWall(21, 0, 23, 7);
  grid.addWall(23, 5, 26, 7);
  return grid;
}

void example_2() {
  using namespace redblobgames;
  SquareGrid const grid = makeDiagram1();
  GridLocation start{8, 8};
  auto parents = breadth_first_search(grid, start);
  drawGrid(grid, nullptr, &parents, nullptr, &start);
}

void example_3() {
  GridLocation start{8, 7}, goal{17, 2};
  SquareGrid grid = makeDiagram1();
  auto came_from = breadth_first_search(grid, start, goal);
  drawGrid(grid, nullptr, &came_from, nullptr, &start, &goal);
}

} // namespace bfs
