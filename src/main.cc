#include <iostream>
#include "spanner/spanner.hh"
#include "spanner/split_tree.hh"
#include "loader/loader.hh"
#include "graph/graph.hh"

void launch_greedy(char **argv)
{
  auto mygraph = Loader::load_graph(argv[1]);
  mygraph.generate_tuples();
  simple_greedy(mygraph, std::atof(argv[2]));
  std::ofstream out_file("result.gv");
  out_file << mygraph;
}

void launch_wspd(char **argv)
{
  auto pair_res = Loader::load_point(argv[1]);
  auto points = pair_res.first;
  auto mygraph = pair_res.second;
  auto tree = SplitTree(points, Rectangle(points)); 
  auto wspd = wspd_decomposition(tree, std::atof(argv[2] - 1));
  std::cout << "================================\n";
  std::cout << "WSPD Run:\n";
  std::cout << "\tNodes:\t" << tree.get_all_nodes().size() << std::endl;
  std::cout << "\tPairs:\t" << wspd.size() << std::endl;
  std::cout << "================================\n";
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
  if (argc < 2)
  {
    std::cout << "Usage: [input_file] [t]\n With input file being"
              << "a csv file name,x,y";
    return 1;
  }
  //launch_greedy(argv);
  launch_wspd(argv);
  return 0;
}
