cmake_minimum_required(VERSION 3.26.4)

project(emulator_6502)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All warning as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)


# add source directory (library)
add_subdirectory(src)

# add example directory
add_subdirectory(examples)

# add test directory
add_subdirectory(test)


