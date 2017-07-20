#include <iostream>
#include "boost/program_options.hpp"
#include "global.hh"

namespace options = boost::program_options;

int main(int argc, char **argv)
{
  options::options_description desc("Options");
  desc.add_options()
    ("help", "print this message")
    ("greedy", "run greedy algorithm")
    ("wspd", "run wspd algorithm")
    ("trace", "print tracing output")
    ("parallel", "run algorithm in parallel")
    ("data", options::value<std::string>()->required(), "dataset in csv")
    ("t", options::value<double>()->required(), "elasticity");
  options::variables_map vm;
  try
  {
    //Parse options
    options::store(options::parse_command_line(argc, argv, desc), vm);

    //Shorthand
    global::trace_debug = vm.count("trace");
    bool parallel = vm.count("parallel");

    if (argc <= 1 || vm.count("help"))
    {
      std::cout << desc << std::endl;
    }
    if (vm.count("greedy"))
    {
      if (parallel)
         launch_par_greedy(vm["data"].as<std::string>(), vm["t"].as<double>());
      else
        launch_greedy(vm["data"].as<std::string>(), vm["t"].as<double>());
    }
    if (vm.count("wspd"))
    {
      if (parallel)
        std::cerr << "Not implemented\n";
      else
        launch_wspd(vm["data"].as<std::string>(), vm["t"].as<double>());
    }
  } catch(options::error& e)
  {
    std::cerr << "Error parsing options\n";
  }
  return 0;
}
