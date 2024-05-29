///
/// \file filegrep.cpp
///

#include "arg_parse.hpp"

#include <iostream>
#include <iterator>

#include <stdlib.h>

int main(int argc, char* argv[])
{
    auto result = EXIT_SUCCESS;

    try {
        auto const arguments = grep::parse_args(argc, argv);
    }
    catch (std::exception const& e) {
        std::cout << e.what() << "\n";
        grep::usage();
        result = EXIT_FAILURE;
    }

    return result;
}
