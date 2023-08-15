enable_testing()

add_executable(
  hello_test
  test.cpp
)

# include the gtest and em6502 lib
target_link_libraries(hello_test em6502 GTest::gtest_main)

target_include_directories(hello_test PUBLIC ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)

gtest_discover_tests(hello_test)