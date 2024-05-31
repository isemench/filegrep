#
# File: CMakeLists.txt
#

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(filegrep VERSION 0.1.0 LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
    include(Sanitizers.cmake)
endif()

add_executable(filegrep
    src/filegrep.cpp
    src/arg_parse.cpp
    src/grepped_file.cpp
    src/file_finder.cpp
    src/launcher.cpp
)

target_include_directories(filegrep
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

include(CTest)
enable_testing()
add_subdirectory(test)
