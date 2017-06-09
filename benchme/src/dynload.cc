#include "dynload.hh"

//Return a vector of function to be
//benchmarked

std::vector<std::function<void(void)>>
load_functions(std::vector<std::string> libs)
{
  std::vector<std::function<void(void)>> res;
  for (std::string lib : libs)
  {
    //Dynamically load library
    void *handler = dlopen(lib.c_str(), RTLD_LAZY);
    if (!handler)
    {
      std::cerr << "Could not open " << lib << std::endl;
      continue;
    }
    dlerror();
    void *symbol = dlsym(handler, "benchme");
    char *error = dlerror();
    if (error)
    {
      std::cerr << "Could load locate symbol \"benchme\" in "
        << lib << std::endl;
      dlclose(handler);
      continue;
    }
    typedef void(*funcptr) (void);
    auto func = reinterpret_cast<funcptr>(symbol);
    res.push_back(std::function<void(void)>(func));
  }
  return res;
}
