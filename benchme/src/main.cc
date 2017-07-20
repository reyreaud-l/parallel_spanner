#include "boost/program_options.hpp"
#include "benchme.hh"

std::string g_file;
float g_t;

int main(int argc, char **argv)
{
  std::vector<std::string> in;
  if (argc < 3)
     std::cout << "USAGE: ./benchme DATASET T libraries...\n";
  g_file = argv[1];
  g_t = atof(argv[2]);
  for (auto i = 3; i < argc; i++)
    in.push_back(std::string(argv[i]));
  auto funcs = load_functions(in);
  auto tests = runner(funcs);
  display_result(tests);
}
