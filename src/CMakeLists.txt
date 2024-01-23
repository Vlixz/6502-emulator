add_library(em6502 STATIC 6502.c cpu.c)

target_include_directories(em6502 PRIVATE ${CMAKE_SOURCE_DIR}/include)

