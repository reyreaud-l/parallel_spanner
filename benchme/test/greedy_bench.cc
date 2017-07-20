#include <iostream>
#include "spanner/spanner.hh"

extern std::string g_file;
extern float g_t;

extern "C"
{
   void benchme(void)
   {
      if (g_file == "")
      {
         std::cout << "File not set\n";
         return;
      }
      if (g_t == 0)
      {
         std::cout << "t parameter not set\n";
         return;
      }
      launch_greedy(g_file, g_t);
   }
}
