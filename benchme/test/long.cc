#include <iostream>

void otherfunc(void)
{
  size_t i = 0;
  while (i < 9999999)
    i++;
}
extern "C"
{
  void benchme(void)
  {
    std::cout << "Running long program...\n";
    size_t i = 0;
    while (i < 200)
    {
      i++;
      otherfunc();
    }
  }
}
