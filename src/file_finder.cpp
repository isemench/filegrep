///
/// \file file_finder.cpp
///

#include "file_finder.hpp"

#include <filesystem>
#include <sstream>

namespace grep {

Find_result find_files(std::string_view const& dir_name)
{
    using Path = std::filesystem::path;
    using Dir_iterator = std::filesystem::recursive_directory_iterator;
    auto const options = std::filesystem::directory_options::skip_permission_denied;

    Find_result result{};
    Path const dir{dir_name};
    try {
        for (auto const& entry : Dir_iterator{dir, options}) {
            if (entry.is_regular_file()) {
                result.files.push_back(entry.path().string());
            }
        }
    }
    catch (std::filesystem::filesystem_error const& e) {
        result.error = e.what();
    }
    return result;
}

} // namespace grep
