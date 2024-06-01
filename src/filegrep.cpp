///
/// \file filegrep.cpp
///

#include "launcher.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    return grep::launch_app(argc, argv, std::cout);
}
