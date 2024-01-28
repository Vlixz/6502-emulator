extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class SED_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~SED_TEST() override { }
};

TEST_F(SED_TEST, SED_IMP_DecimalFlagSet) {
    cpu.D = 0;

    // Start inline program
    cpu.memory[0xFFFC] = SED_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, SED_IMP_CYCLES);

    ASSERT_EQ(cycles, SED_IMP_CYCLES);

    ASSERT_TRUE(cpu.D);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(SED_TEST, SED_IMP_DecimalFlagStaysSetWhenSettingItMultipleTimes) {
    cpu.D = 0;

    // Start inline program
    cpu.memory[0xFFFC] = SED_IMP_OPCODE;
    cpu.memory[0xFFFD] = SED_IMP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, SED_IMP_CYCLES * 2);

    ASSERT_EQ(cycles, SED_IMP_CYCLES * 2);

    ASSERT_TRUE(cpu.D);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
