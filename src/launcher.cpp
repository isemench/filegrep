///
/// \file launcher.cpp
///

#include "launcher.hpp"

#include "arg_parse.hpp"
#include "file_finder.hpp"
#include "grepped_file.hpp"

#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <regex>

#include <stdlib.h>

namespace grep {

std::int32_t launch_app(int const arg_count, char* const args_list[])
{
    auto result = EXIT_SUCCESS;

    try {
        auto const arguments = parse_args(arg_count, args_list);
        auto const file_list = find_files(arguments.dir);

        File_istream_creator creator =
            [](std::string const& file_name) -> std::unique_ptr<std::istream> {
            return std::make_unique<std::ifstream>(file_name);
        };

        auto regex = std::regex(arguments.pattern.data());
        for (auto const& file : file_list) {
            auto file_to_grep = Grepped_file(file, regex, std::cout, creator);
            std::async(std::launch::async, &Grepped_file::find_and_print_results, &file_to_grep)
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

} // namespace grep
