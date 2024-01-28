extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class TAY_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~TAY_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(TAY_TEST, TAY_IP_TransferAccumulatorIntoY) {
    cpu.A = 0x0F;

    // Start inline program
    cpu.memory[0xFFFC] = TAY_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAY_IP_CYCLES);

    ASSERT_EQ(cycles, TAY_IP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x0F);

    ASSERT_FALSE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TAY_TEST, TAY_IP_TransferAccumulatorIntoYNegative) {
    cpu.A = 0b10001111;

    // Start inline program
    cpu.memory[0xFFFC] = TAY_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAY_IP_CYCLES);

    ASSERT_EQ(cycles, TAY_IP_CYCLES);

    ASSERT_EQ(cpu.Y, 0b10001111);

    ASSERT_TRUE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TAY_TEST, TAY_IP_TransferAccumulatorIntoYZero) {
    cpu.A = 0x00;

    // Start inline program
    cpu.memory[0xFFFC] = TAY_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAY_IP_CYCLES);

    ASSERT_EQ(cycles, TAY_IP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_FALSE(cpu.N);
    ASSERT_TRUE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
