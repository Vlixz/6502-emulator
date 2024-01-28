extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class SEI_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~SEI_TEST() override { }
};

TEST_F(SEI_TEST, SEI_IMP_InterruptFlagSet) {
    cpu.I = 0;

    // Start inline program
    cpu.memory[0xFFFC] = SEI_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, SEI_IMP_CYCLES);

    ASSERT_EQ(cycles, SEI_IMP_CYCLES);

    ASSERT_TRUE(cpu.I);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(SEI_TEST, SEI_IMP_InterruptFlagStaysSetWhenSettingItMultipleTimes) {
    cpu.I = 0;

    // Start inline program
    cpu.memory[0xFFFC] = SEI_IMP_OPCODE;
    cpu.memory[0xFFFD] = SEI_IMP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, SEI_IMP_CYCLES * 2);

    ASSERT_EQ(cycles, SEI_IMP_CYCLES * 2);

    ASSERT_TRUE(cpu.I);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
