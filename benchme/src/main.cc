#include "timer.hh"
#include "dynload.hh"

int main(int argc, char **argv)
{
  std::vector<std::string> in;
  for (auto i = 1; i < argc; i++)
    in.push_back(std::string(argv[i]));
  auto funcs = load_functions(in);
  for(const auto& func : funcs)
  {
    double time = 0;
    {
      auto timer = scope_timer(time);
      func();
    }
    std::cout << "Run in " << time << std::endl;
  }
}
