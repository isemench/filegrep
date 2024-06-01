///
/// \file launcher.cpp
///

#include "launcher.hpp"

#include "arg_parser.hpp"
#include "file_finder.hpp"
#include "grepped_file.hpp"

#include <fstream>
#include <future>
#include <memory>
#include <ostream>
#include <regex>

#include <stdlib.h>

namespace grep {

std::int32_t launch_app(int const arg_count, char* const args_list[], std::ostream& output)
{
    auto result = EXIT_SUCCESS;

    try {
        auto const arguments = parse_args(arg_count, args_list);
        auto const find_result = find_files(arguments.dir);

        if (!find_result.error.empty()) {
            throw std::invalid_argument(find_result.error);
        }

        File_istream_creator creator =
            [](std::string const& file_name) -> std::unique_ptr<std::istream> {
            return std::make_unique<std::ifstream>(file_name);
        };

        auto pattern = std::regex(arguments.pattern.data());
        auto files_to_grep = std::vector<Grepped_file>();
        auto tasks = std::vector<std::future<std::string>>{};
        for (auto const& file : find_result.files) {
            files_to_grep.emplace_back(file, pattern, creator);
        }

        for (auto& file : files_to_grep) {
            tasks.push_back(
                std::async(std::launch::async, &Grepped_file::find_and_print_results, &file));
        }

        for (auto& task : tasks) {
            output << task.get();
        }
    }
    catch (std::exception const& e) {
        output << e.what() << "\n";
        grep::usage(output);
        result = EXIT_FAILURE;
    }

    return result;
}

} // namespace grep
