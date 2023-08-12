add_executable(example_1 example1.c)

target_link_libraries(example_1 PUBLIC em6502)

target_include_directories(example_1 PUBLIC ${CMAKE_SOURCE_DIR}/include)