add_executable(em6502test test.c)

target_link_libraries(em6502test PUBLIC cpu6502)

target_include_directories(em6502test PUBLIC ${CMAKE_SOURCE_DIR}/include)

