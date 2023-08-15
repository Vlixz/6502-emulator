enable_testing()

add_executable(
  hello_test
  test.cpp
)

target_include_directories(hello_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(hello_test em6502 GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(hello_test)

# add_executable(hello_test test.cpp)

# target_link_libraries(hello_test PUBLIC em6502)

# target_include_directories(hello_test PUBLIC ${CMAKE_SOURCE_DIR}/include)