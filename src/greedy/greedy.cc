#include "greedy/greedy.hh"


void simple_greedy(Graph<>& graph, float t)
{
  //tuples are already sorted when generated in graph
  auto tuples = graph.tuples_get();
  std::size_t i = 0;
  for (const auto& tuple : tuples)
  {
     auto d = shortest_distance(graph, std::get<0>(tuple), std::get<1>(tuple));
     std::cout << std::endl << "Current: " << i << ", Target: " << tuples.size() << std::endl;
     std::cout << graph[std::get<0>(tuple)] << std::endl;
     std::cout << graph[std::get<1>(tuple)] << std::endl;
     std::cout << "Dist: " << std::get<2>(tuple) << std::endl;
     std::cout << "Dijkstra Dist: " << d << std::endl;
     if (d > t * std::get<2>(tuple))
     {
        std::cout << "Added\n";
        boost::add_edge(std::get<0>(tuple), std::get<1>(tuple), graph);
     }
     if (i == 19)
       break;
     i++;
  }
}

double shortest_distance(Graph<>& graph,
                         Graph<>::vertex_descriptor src,
                         Graph<>::vertex_descriptor dest)
{
   return dijkstra(graph, src, dest)[dest];
}

double pythagore(Graph<>& graph,
                 Graph<>::vertex_descriptor src,
                 Graph<>::vertex_descriptor dest)
{
   auto pt1 = graph[src];
   auto pt2 = graph[dest];
   return std::sqrt(std::pow(pt2.x - pt1.x, 2)
                    + std::pow(pt2.y - pt1.y, 2));

}

std::map<Graph<>::vertex_descriptor, double>
dijkstra(Graph<>& graph, Graph<>::vertex_descriptor src,
         Graph<>::vertex_descriptor dest)
{
  (void)dest;
   std::map<Graph<>::vertex_descriptor, double> dist_map;
   dist_map[src] = 0;

   using prio_pair = std::pair<Graph<>::vertex_descriptor, double>;
   auto cmp = [](prio_pair left, prio_pair right){
      return left.second > right.second;
   };
   std::priority_queue<prio_pair, std::vector<prio_pair>,
                       decltype(cmp)> pqueue(cmp);
   std::set<prio_pair> worked;
   for (auto it = boost::vertices(graph); it.first != it.second; ++it.first)
   {
      if (*it.first != src)
         dist_map[*it.first] = INT_MAX;
   }
   pqueue.emplace(src, 0);

   while (!pqueue.empty())
   {
      auto pair = pqueue.top();
      auto vertice = pqueue.top().first;
      pqueue.pop();
      if (worked.find(pair) != worked.end())
      {
        std::cout << "skip\n";
        continue;
      }
      worked.emplace(pair);

      for (auto it = boost::adjacent_vertices(vertice, graph);
           it.first != it.second; it.first++)
      {
         auto alt = dist_map[vertice] + pythagore(graph, vertice, *it.first);
         if (alt < dist_map[*it.first])
         {
            dist_map[*it.first] = alt;
            pqueue.emplace(*it.first, alt);
         }
      }
   }

   return dist_map;
}
