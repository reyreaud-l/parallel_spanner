#pragma once

#include <iostream>
#include <fstream>
#include "graph/graph.hh"

class Loader
{
public:
   static Graph<> Load(std::string name);
};
