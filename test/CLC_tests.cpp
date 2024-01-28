extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class CLC_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~CLC_TEST() override { }
};

TEST_F(CLC_TEST, CLC_IP_ClearsCarryFlag) {
    cpu.C = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLC_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, CLC_IMP_CYCLES);

    ASSERT_EQ(cycles, CLC_IMP_CYCLES);

    ASSERT_FALSE(cpu.C);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(CLC_TEST, CLC_IP_DoesNotChangeClearedCarryFlag) {
    cpu.C = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLC_IMP_OPCODE;
    cpu.memory[0xFFFD] = CLC_IMP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, CLC_IMP_CYCLES * 2);

    ASSERT_EQ(cycles, CLC_IMP_CYCLES * 2);

    ASSERT_FALSE(cpu.C);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
