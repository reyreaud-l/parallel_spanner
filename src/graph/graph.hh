#pragma once

#include "boost/functional/hash.hpp"
#include "boost/graph/detail/edge.hpp"
#include "boost/graph/adjacency_list.hpp"

#include <cmath>
#include <vector>
#include <tuple>
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
  public:
  using super_type = boost::adjacency_list<boost::setS, boost::vecS,
    boost::bidirectionalS, VertexLabel, EdgeLabel, name_prop_type>;
  using vertex_descriptor = typename super_type::vertex_descriptor;
  using tuple = std::tuple<vertex_descriptor, vertex_descriptor, double>;
  using tuples_vector = std::vector<tuple>;

  void generate_tuples()
  {
    tuples_.clear();
    for(auto it = boost::vertices(*this); it.first != it.second; ++it.first)
    {
      for (auto it2 = it; it2.first != it2.second; ++it2.first)
      {
        if (*it.first == *it2.first)
          continue;
        auto pt1 = (*this)[(*it.first)];
        auto pt2 = (*this)[(*it2.first)];
        auto dist = std::sqrt(std::pow(pt2.x - pt1.x, 2)
            + std::pow(pt2.y - pt1.y, 2));
        tuples_.push_back(std::make_tuple<>(*it.first, *it2.first, dist));
      }
    }
    std::sort(tuples_.begin(), tuples_.end(), [](tuple a, tuple b)
        {
          auto d1 = std::get<2>(a);
          auto d2 = std::get<2>(b);
          return d1 < d2;
        });
  }

  tuples_vector tuples_get()
  {
    return tuples_;
  }

  private:
  tuples_vector tuples_;

  friend std::ostream& operator<<(std::ostream& ostr_, const Graph& p)
  {
    (void)p;
    ostr_ << "lol\n";
    return ostr_;
  }
};
