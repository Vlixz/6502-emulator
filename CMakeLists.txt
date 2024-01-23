cmake_minimum_required(VERSION 3.27.1)

project(emulator_6502)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All warning as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# add source directory (library)
add_subdirectory(src)

# add example directory
add_subdirectory(examples)

# add test directory
add_subdirectory(test)


