extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class CLI_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~CLI_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(CLI_TEST, CLI_IP_InterruptFlagCleared) {
    cpu.I = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLI_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, CLC_IP_CYCLES);

    ASSERT_EQ(cycles, CLC_IP_CYCLES);

    ASSERT_FALSE(cpu.I);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(CLI_TEST, CLI_IP_DoesNotChangeClearedInterruptFlag) {
    cpu.I = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLI_IP_OPCODE;
    cpu.memory[0xFFFD] = CLI_IP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, CLI_IP_CYCLES * 2);

    ASSERT_EQ(cycles, CLI_IP_CYCLES * 2);

    ASSERT_FALSE(cpu.I);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
