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
  auto points = Loader::load_point(argv[1]);
  auto tree = SplitTree(points, Rectangle(points)); 
  std::cout << tree.get_all_nodes().size() << std::endl;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: [t] [input_file]\n With input file being"
              << "a csv file name,x,y";
    return 1;
  }
  //launch_greedy(argv);
  launch_wspd(argv);
  return 0;
}
