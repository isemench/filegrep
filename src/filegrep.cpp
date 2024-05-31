///
/// \file filegrep.cpp
///

#include "arg_parse.hpp"
#include "file_finder.hpp"
#include "grepped_file.hpp"

#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <memory>
#include <regex>

#include <stdlib.h>

int main(int argc, char* argv[])
{
    auto result = EXIT_SUCCESS;

    try {
        auto const arguments = grep::parse_args(argc, argv);
        auto const file_list = grep::enumerate_dir(arguments.dir);

        grep::File_istream_creator creator =
            [](std::string const& file_name) -> std::unique_ptr<std::istream> {
            return std::make_unique<std::ifstream>(file_name);
        };

        auto regex = std::regex(arguments.pattern.data());
        for (auto const& file : file_list) {
            auto file_to_grep = grep::Grepped_file(file, regex, std::cout, creator);
            std::async(std::launch::async, &grep::Grepped_file::find_and_print_results,
                       &file_to_grep)
                .get();
        }
    }
    catch (std::exception const& e) {
        std::cout << e.what() << "\n";
        grep::usage();
        result = EXIT_FAILURE;
    }

    return result;
}
