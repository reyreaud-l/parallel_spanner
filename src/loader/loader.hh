#pragma once

#include <iostream>
#include <fstream>
#include "spanner/rectangle.hh"
#include "graph/graph.hh"

class Loader
{
public:
   static Graph<> load_graph(std::string name);
   static std::pair<std::vector<Point>, Graph<>> load_point(std::string filename);
};
