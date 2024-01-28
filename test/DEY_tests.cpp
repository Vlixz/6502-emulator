extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class DEY_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~DEY_TEST() override { }
};

TEST_F(DEY_TEST, DEY_IMP_DecrementsXZeroNonNegative) {
    cpu.Y = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = DEY_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEY_IMP_CYCLES);

    ASSERT_EQ(cycles, DEY_IMP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);
    ASSERT_TRUE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(DEY_TEST, DEY_IMP_DecrementsXNonZeroNegative) {
    cpu.Y = 0x00;

    // Start inline program
    cpu.memory[0xFFFC] = DEY_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEY_IMP_CYCLES);

    ASSERT_EQ(cycles, DEY_IMP_CYCLES);

    ASSERT_EQ(cpu.Y, 0xFF);
    ASSERT_TRUE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(DEY_TEST, DEY_IMP_DecrementsXNonZeroNonNegative) {
    cpu.Y = 0x02;

    // Start inline program
    cpu.memory[0xFFFC] = DEY_IMP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEY_IMP_CYCLES);

    ASSERT_EQ(cycles, DEY_IMP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x01);
    ASSERT_FALSE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
