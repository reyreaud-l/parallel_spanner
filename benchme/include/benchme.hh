#pragma once

#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <vector>
#include <chrono>

using func_lib_vector = std::vector<std::pair<std::function<void(void)>, std::string>>;

using std::chrono::steady_clock;
using std::chrono::nanoseconds;
struct scope_timer
{
  scope_timer(double &s)
  : seconds(s)
  , t0(steady_clock::now())
  {}

  ~scope_timer()
  {
    std::chrono::duration<double> diff = steady_clock::now() - t0;
    seconds = diff.count();
  }

  double& seconds;
  steady_clock::time_point t0;
};

class Test
{
  public:
    Test(std::function<void(void)>, std::string);
    void run();

    std::string name_get() { return name_; }
    double time_get() { return time_; }
    std::string name_get() const { return name_; }
    double time_get() const { return time_; }

  private:
    std::function<void(void)> sub_;
    std::string name_;
    double time_;
};

std::ostream& operator<<(std::ostream&, const Test&);

func_lib_vector load_functions(std::vector<std::string>);
std::vector<Test> runner(func_lib_vector funcs);
void display_result(std::vector<Test> tests);
