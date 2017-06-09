#include <iostream>

extern "C"
{
  void benchme(void)
  {
    std::cout << "Running short program...\n";
    size_t i = 0;
    while (i < 9999999)
      i++;
  }
}
