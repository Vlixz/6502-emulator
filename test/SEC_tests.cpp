extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class SEC_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~SEC_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(SEC_TEST, SEC_IP_CarryFlagSet) {
    cpu.C = 0;

    // Start inline program
    cpu.memory[0xFFFC] = SEC_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, SEC_IP_CYCLES);

    ASSERT_EQ(cycles, SEC_IP_CYCLES);

    ASSERT_TRUE(cpu.C);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(SEC_TEST, SEC_IP_CarryFlagStaysSetWhenSettingItMultipleTimes) {
    cpu.C = 1;

    // Start inline program
    cpu.memory[0xFFFC] = SEC_IP_OPCODE;
    cpu.memory[0xFFFD] = SEC_IP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, SEC_IP_CYCLES * 2);

    ASSERT_EQ(cycles, SEC_IP_CYCLES * 2);

    ASSERT_TRUE(cpu.C);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
