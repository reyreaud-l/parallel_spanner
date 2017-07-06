#pragma once

#include <iostream>
#include <fstream>
#include "graph/graph.hh"

class Loader
{
public:
   Graph<> Load(std::string name);
};
