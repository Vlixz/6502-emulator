cmake_minimum_required(VERSION 3.27.1)

project(emulator_6502)

# All warning as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON) 

# add source directory (library)
add_subdirectory(src)

# add example directory
add_subdirectory(examples)
