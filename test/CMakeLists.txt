#
# File: test/CMakeLists.txt
#

include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(filegrep_test
    ${PROJECT_SOURCE_DIR}/src/arg_parse.cpp
    ${PROJECT_SOURCE_DIR}/src/grepped_file.cpp
    ${PROJECT_SOURCE_DIR}/src/file_finder.cpp

    src/arg_parser_test.cpp
    src/file_finder_test.cpp
    src/grepped_file_test.cpp
)

target_include_directories(filegrep_test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(filegrep_test
    PRIVATE
        GTest::gtest_main
)

gtest_discover_tests(filegrep_test)

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
