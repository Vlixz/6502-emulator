extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class NOP_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~NOP_TEST() override { }
};

TEST_F(NOP_TEST, NOP_IP_DoesNothing) {
    // Start inline program
    cpu.memory[0xFFFC] = NOP_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, NOP_IMP_CYCLES);

    ASSERT_EQ(cycles, NOP_IMP_CYCLES);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
