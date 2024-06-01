# Filegrep

## Purpose

The filegrep utility looks for matches for the given pattern, in the given directory and its sub-directories.

The utility accepts two parameters, the first one is the pattern in form of [Modified ECMAScript regular expression grammar](https://en.cppreference.com/w/cpp/regex/ecmascript), the second one is the directory where its searches for the pattern recursively.

## Software architecture and detailed design

The utility is implemented in C++ 17 language. The build system is CMake v.3.22. Tests are part of the project, the test framework is Google Test v.1.14.0. The above version of Google Test framework is automatically downloaded during build.

The project directory contains implementation in src/, header files in include/, and test implementation in test/. CMake test script also contains configuration options that enable sanitizers (turned off by default).

The implementation consists of four units. The main() function passes control to the Launcher unit, to simplify testing of the whole code base.

Launcher uses three other units. The first one is Argument Parser for checking  parameters passed to the utility and getting their values. After that, Launcher calls File Finder to perform the recursive search of **regular** files and get the list of them. For every file found, Launcher calls Grepped File asynchronously. Every instance of Grepped File performs matching of the given pattern and collects the output as a string. All the output strings are then collected by Launcher and printed on the console.

The instance of standard output is passed as a parameter, to be able to redirect output to a string stream and check it against the expected value. File streams are passed as polymorphic pointers, to be able to mock them with string streams in tests.

The test suite is separated for every unit (Launcher is not included, unfortunately). Units are tested for positive and negative use cases, an attempt was made to cover as much as possible, testing strategies are applied e.g. boundary testing and equivalent classes.

## Error reporting

In case of wrong number of arguments passed to the utility, it prints a warning message and usage information to the standard output. If the given directory does not exist or cannot be accessed, a warning message is printed. In case of no matches, the utility does not print anything.
