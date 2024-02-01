add_library(cpu6502 STATIC 6502.c cpu.c instruction.c memory.c instruction_matrix.c)

target_include_directories(cpu6502 PRIVATE ${CMAKE_SOURCE_DIR}/include)

