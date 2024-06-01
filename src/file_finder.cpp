///
/// \file file_finder.cpp
///

#include "file_finder.hpp"

#include <filesystem>

namespace grep {

File_list find_files(std::string_view const& dir_name)
{
    using Path = std::filesystem::path;
    using Dir_iterator = std::filesystem::recursive_directory_iterator;

    File_list result{};
    Path const dir{dir_name};
    for (auto const& entry : Dir_iterator{dir}) {
        if (entry.is_regular_file()) {
            result.push_back(entry.path().string());
        }
    }
    return result;
}

} // namespace grep
