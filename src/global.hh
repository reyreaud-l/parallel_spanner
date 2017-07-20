#pragma once
#include <string>

namespace global
{
  extern bool trace_debug;
}
void launch_par_greedy(std::string file, double t);
void launch_greedy(std::string file, double t);
void launch_wspd(std::string file, double t);
