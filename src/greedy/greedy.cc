#include "greedy/greedy.hh"

void simple_greedy(Graph<>& graph, float t)
{
  (void)t;
  //tuples are already sorted when generated in graph
  auto tuples = graph.tuples_get();
  for (const auto& tuple : tuples)
  {
    (void)tuple;
  }
}
