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
        auto files_to_grep = std::vector<Grepped_file>();
        auto tasks = std::vector<std::future<std::string>>{};
        for (auto const& file : file_list) {
            files_to_grep.emplace_back(file, regex, std::cout, creator);
        }
        for (auto& file_to_grep : files_to_grep) {
            tasks.push_back(std::async(std::launch::async, &Grepped_file::find_and_print_results,
                                       &file_to_grep));
        }

        for (auto& task : tasks) {
            std::cout << task.get();
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
