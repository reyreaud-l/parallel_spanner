#include <iostream>
#include "graph.hh"

struct vertice
{
  public:
    int x;
    int y;
};

int main(void)
{
  auto mygraph = Graph<vertice>();
  for(int i = 0; i < 10; i++)
  {
    auto vertice = boost::add_vertex(mygraph);
    auto& data = mygraph[vertice];
    data.x = i;
    data.y = i;
  }

  auto it = boost::vertices(mygraph);
  for (;it.first != it.second; it.first++)
  {
    auto vertice = *it.first;
    auto data = mygraph[vertice];
    std::cout << "Node: x -> " << data.x
      << "\n      y -> " << data.y << std::endl;
  }
  std::cout << mygraph;
  return 0;
}
