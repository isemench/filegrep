cmake_minimum_required(VERSION 3.0.0)
project(filegrep VERSION 0.1.0 LANGUAGES CXX)

add_executable(filegrep src/filegrep.cpp)

include(CTest)
enable_testing()
