#include "benchme.hh"

//Return a vector of function to be
//benchmarked

func_lib_vector load_functions(std::vector<std::string> libs)
{
  func_lib_vector res;
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
    else
    {
       std::cerr << "Symbol \"benchme\" in "
                 << lib << " has been loaded" << std::endl;
    }
    typedef void(*funcptr) (void);
    auto func = reinterpret_cast<funcptr>(symbol);
    res.push_back(std::make_pair<>(std::function<void(void)>(func), lib));
  }
  return res;
}
