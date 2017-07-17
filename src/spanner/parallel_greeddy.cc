#include "spanner/spanner.hh"


using prio_pair = std::pair<Graph<>::vertex_descriptor, double>;
class prio_compare
{
public:
   bool operator()(const prio_pair left, const prio_pair right){
      return left.second > right.second;
   }
};



Graph<> *graph_;
Graph<>::vertex_descriptor dest_;
Graph<>::vertex_descriptor src_;
size_t max_spawn;
std::vector<double> dist_vec;
std::vector<double> real_distance;
tbb::concurrent_priority_queue<prio_pair, prio_compare> pqueue;
tbb::spin_mutex *locks;
tbb::task_group *sp_group;
tbb::atomic<size_t> num_spawn;

void shortpath()
{
   prio_pair vertx;
   while (!pqueue.try_pop(vertx))
   {
      Graph<>::vertex_descriptor vertice = vertx.first;
      if (vertice == src_)
         continue;;
      double f = vertx.second;
      double old_g_u = 0.0;
      {
         tbb::spin_mutex::scoped_lock l(locks[vertice]);
         if (f > real_distance[vertice])
            continue;
         old_g_u = dist_vec[vertice];
      }
      for (auto it = boost::adjacent_vertices(vertice, *graph_);
           it.first != it.second; it.first++)
      {
         auto alt = old_g_u + pythagore(*graph_, vertice, *it.first);
         double new_real = 0.0;
         bool push = false;
         {
            tbb::spin_mutex::scoped_lock l(locks[*it.first]);
            if (alt < dist_vec[*it.first])
            {
               dist_vec[*it.first] = alt;
               new_real = alt;
               real_distance[*it.first] = new_real;
               push = true;
            }
         }
         if (push)
         {
            pqueue.push(std::make_pair(*it.first, alt));
            size_t n_spawn = ++num_spawn;
            if (n_spawn < max_spawn)
            {
               sp_group->run([]{ shortpath(); });
            }
            else
               --num_spawn;
         }
      }
   }
   --num_spawn;
}

double
parallel_shortpath(Graph<>& graph, Graph<>::vertex_descriptor src,
                  Graph<>::vertex_descriptor dest)
{
   locks = new tbb::spin_mutex[graph.number_nodes];
   graph_ = &graph;
   src_ = src;
   dest_ = dest;
   sp_group = new tbb::task_group;
   dist_vec.resize(graph.number_nodes);
   real_distance.resize(graph.number_nodes);
   dist_vec[src] = 0.0;
   real_distance[src] = pythagore(graph, src, dest);
//   std::vector<bool> worked;

   pqueue.push(std::make_pair(src, real_distance[src]));
   sp_group->run([](){ shortpath(); });
   sp_group->wait();
   delete sp_group;
   delete locks;
   return dist_vec[dest];
}


void parallel_greedy(Graph<>& graph, float t)
{
  //tuples are already sorted when generated in graph
  auto tuples = graph.tuples_get();
  std::size_t i = 0;
  for (const auto& tuple : tuples)
  {
     auto d = parallel_shortpath(graph, std::get<0>(tuple), std::get<1>(tuple));
     if (i % 1000 == 0 && global::trace_debug)
      std::cout << "Current: " << i / 1000 << ", Target: " << tuples.size() / 1000 << std::endl;
     if (d > t * std::get<2>(tuple))
     {
        boost::add_edge(std::get<0>(tuple), std::get<1>(tuple), graph);
     }
     i++;
  }
}
