#pragma once
#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <vector>

std::vector<std::function<void(void)>> load_functions(std::vector<std::string>);
