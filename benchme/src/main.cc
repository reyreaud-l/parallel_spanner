#include "boost/program_options.hpp"
#include "benchme.hh"

int main(int argc, char **argv)
{
  std::vector<std::string> in;
  for (auto i = 1; i < argc; i++)
    in.push_back(std::string(argv[i]));
  auto funcs = load_functions(in);
  auto tests = runner(funcs);
  display_result(tests);
}
