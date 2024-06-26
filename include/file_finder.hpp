///
/// \file file_finder.hpp
///

#ifndef FILE_FINDER_HPP
#define FILE_FINDER_HPP

#include <string>
#include <vector>

namespace grep {

using File_list = std::vector<std::string>;

struct Find_result {
    File_list files{};
    std::string error{};
};

Find_result find_files(std::string_view const& dir_name);

} // namespace grep

#endif // FILE_FINDER_HPP
