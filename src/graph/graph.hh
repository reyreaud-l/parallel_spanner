#pragma once

#include "boost/functional/hash.hpp"
#include "boost/graph/detail/edge.hpp"
#include "boost/graph/adjacency_list.hpp"

#include <vector>
#include <string>
#include <set>

struct vertice
{
  public:
    int x;
    int y;
  private:
    friend std::ostream& operator<<(std::ostream& ostr_, vertice& v)
    {
      ostr_ << "x: " << v.x << " y: " << v.y;
      return ostr_;
    }
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
  using pair_set = std::set<std::pair<vertex_descriptor, vertex_descriptor>>;

  public:
  void generate_pairs()
  {
    for(auto it = boost::vertices(*this); it.first != it.second; ++it.first)
    {
      for (auto it2 = it; it2.first != it2.second; ++it2.first)
      {
        if (*it.first == *it2.first)
          continue;
        pairs_.emplace(std::make_pair<>(*it.first, *it2.first));
      }
    }
  }

  pair_set pairs_get()
  {
    return pairs_;
  }

  private:
  pair_set pairs_;

  friend std::ostream& operator<<(std::ostream& ostr_, const Graph& p)
  {
    (void)p;
    ostr_ << "lol\n";
    return ostr_;
  }
};
