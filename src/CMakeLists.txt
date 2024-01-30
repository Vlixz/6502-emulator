add_subdirectory(cpu6502)

add_executable(em6502 main.c)

target_link_libraries(em6502 PUBLIC cpu6502)

target_include_directories(em6502 PUBLIC ${CMAKE_SOURCE_DIR}/include)

