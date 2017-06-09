#include "dumy.hh"
#include "dynload.hh"

int main(void)
{
  auto funcs = load_functions(std::vector<std::string>{ "./libbenchme_test.so" });
  for(const auto& func : funcs)
    func();
} 
