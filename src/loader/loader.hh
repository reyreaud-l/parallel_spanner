#pragma once

#include <iostream>
#include <fstream>
#include "spanner/rectangle.hh"
#include "graph/graph.hh"

class Loader
{
public:
   static Graph<> load_graph(std::string name);
   static std::vector<Point> load_point(std::string name);
};
