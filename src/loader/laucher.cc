#include <iostream>
#include "boost/program_options.hpp"
#include "spanner/spanner.hh"
#include "spanner/split_tree.hh"
#include "loader/loader.hh"
#include "graph/graph.hh"

namespace options = boost::program_options;
namespace global
{
  bool trace_debug;
}

void launch_greedy(std::string file, double t)
{
  auto mygraph = Loader::load_graph(file);
  mygraph.generate_tuples();
  simple_greedy(mygraph, t);
  std::ofstream out_file("result.gv");
  out_file << mygraph;
}

void launch_par_greedy(std::string file, double t)
{
  auto mygraph = Loader::load_graph(file);
  mygraph.generate_tuples();
  parallel_greedy(mygraph, t);
  std::ofstream out_file("result.gv");
  out_file << mygraph;
}

void launch_wspd(std::string file, double t)
{
  auto pair_res = Loader::load_point(file);
  auto points = pair_res.first;
  auto mygraph = pair_res.second;
  auto tree = SplitTree(points, Rectangle(points)); 
  auto wspd = wspd_decomposition(tree, t - 1);
  if (global::trace_debug)
  {
    std::cout << "================================\n";
    std::cout << "WSPD Run:\n";
    std::cout << "\tNodes:\t" << tree.get_all_nodes().size() << std::endl;
    std::cout << "\tPairs:\t" << wspd.size() << std::endl;
    std::cout << "================================\n";
  }
  for (auto pair : wspd)
  {
    auto left = pair.first;
    auto right = pair.second;
    boost::add_edge(left[rand() % left.size()].vertice,
        right[rand() % right.size()].vertice, mygraph);
  }
  std::ofstream out_file("result.gv");
  out_file << mygraph;
}
