#pragma once

#include "boost/functional/hash.hpp"
#include "boost/graph/detail/edge.hpp"
#include "boost/graph/adjacency_list.hpp"

#include <vector>
#include <string>

struct vertice
{
  public:
    int x;
    int y;
};

struct edge
{
  public:
    double cost;
};

using name_prop_type = boost::property<boost::graph_name_t, std::string>;

template <typename VertexLabel = vertice, typename EdgeLabel = edge>
class Graph : public boost::adjacency_list<boost::setS, boost::vecS,
  boost::bidirectionalS, VertexLabel, EdgeLabel, name_prop_type>
{
  using super_type = boost::adjacency_list<boost::setS, boost::vecS,
    boost::bidirectionalS, VertexLabel, EdgeLabel, name_prop_type>;
  using vertex_descriptor = typename super_type::vertex_descriptor;

  friend std::ostream& operator<<(std::ostream& ostr_, const Graph& p)
  {
    (void)p;
    ostr_ << "lol\n";
    return ostr_;
  }
  public:
    virtual ~Graph() {};
};
