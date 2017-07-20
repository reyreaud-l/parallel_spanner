#include "benchme.hh"

std::vector<Test> runner(func_lib_vector funcs)
{
  std::vector<Test> res;
  for(const auto& func : funcs)
  {
    auto test = Test(func.first, func.second);
    test.run();
    res.push_back(test);
  }
  return res;
}

Test::Test(std::function<void(void)> sub, std::string name)
  : sub_(sub)
  , name_(name)
{}

void Test::run()
{
  auto timer = scope_timer(time_);
  sub_();
}


void display_result(std::vector<Test> tests)
{
  for (const auto& test : tests)
    std::cout << test;
}

std::ostream& operator<<(std::ostream& os_, const Test& test)
{
  os_ << std::endl << "----------------------" << std::endl;
  os_ << "Benchmark: " << test.name_get() << std::endl;
  os_ << "Execution time: " << test.time_get() << std::endl;
  os_ << "----------------------" << std::endl;
  return os_;
}
