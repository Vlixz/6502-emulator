cmake_minimum_required(VERSION 3.26.4)

project(em6502)

add_subdirectory(6502)

add_executable(em6502 main.c)

target_link_libraries(em6502 PUBLIC cpu6502)

target_link_libraries(em6502 PUBLIC ${CURSES_LIBRARIES})

target_include_directories(em6502 PUBLIC ${CMAKE_SOURCE_DIR}/include)
