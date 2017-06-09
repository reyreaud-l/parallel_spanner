#pragma once

#include <chrono>


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
