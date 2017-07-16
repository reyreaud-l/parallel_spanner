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

int main(int argc, char **argv)
{
  options::options_description desc("Options");
  desc.add_options()
    ("help", "print this message")
    ("greedy", "run greedy algorithm")
    ("wspd", "run wspd algorithm")
    ("trace", "print tracing output")
    ("parallel", "run algorithm in parallel")
    ("data", options::value<std::string>()->required(), "dataset in csv")
    ("t", options::value<double>()->required(), "elasticity");
  options::variables_map vm;
  try
  {
    //Parse options
    options::store(options::parse_command_line(argc, argv, desc), vm);

    //Shorthand
    global::trace_debug = vm.count("trace");
    bool parallel = vm.count("parallel");

    if (argc <= 1 || vm.count("help"))
    {
      std::cout << desc << std::endl;
    }
    if (vm.count("greedy"))
    {
      if (parallel)
        std::cerr << "Not implemented\n";
      else
        launch_greedy(vm["data"].as<std::string>(), vm["t"].as<double>());
    }
    if (vm.count("wspd"))
    {
      if (parallel)
        std::cerr << "Not implemented\n";
      else
        launch_wspd(vm["data"].as<std::string>(), vm["t"].as<double>());
    }
  } catch(options::error& e)
  {
    std::cerr << "Error parsing options\n";
  }
  return 0;
}
