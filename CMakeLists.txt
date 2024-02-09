cmake_minimum_required(VERSION 3.26.4)

project(emulator_6502)

# Set the C standard version
set(CMAKE_C_STANDARD 11) 

# All warning as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# add source directory (library)
add_subdirectory(src)

# add test directory
add_subdirectory(test)


