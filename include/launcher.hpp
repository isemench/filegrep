///
/// \file launcher.hpp
///

#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include <cstdint>
#include <iosfwd>

namespace grep {

std::int32_t launch_app(int const arg_count, char* const args_list[], std::ostream& output);

} // namespace grep

#endif // LAUNCHER_HPP
