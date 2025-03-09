Algorithm

1. Initialize all distances of all nodes as infinites.
2. Create an empty priority queue (min-heap). Low weight (distance) more needed.
3. Insert source node to the priority queue.
4. While priority queue is not empty:

    * Extract minimum weight node
    * Loop through all adjacent list
    * If there is shortest path, update current
    * If node is visited, do nothing