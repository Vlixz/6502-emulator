extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class TAX_TEST : public ::testing::Test {
  protected:
    CPU_6502 cpu;

    void SetUp() override { em6502_reset(&cpu); }

    ~TAX_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(TAX_TEST, TAX_IP_TransferAccumulatorIntoX) {
    cpu.A = 0x0F;

    // Start inline program
    cpu.memory[0xFFFC] = TAX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAX_IP_CYCLES);

    ASSERT_EQ(cycles, TAX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0x0F);

    ASSERT_FALSE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TAX_TEST, TAX_IP_TransferAccumulatorIntoXNegative) {
    cpu.A = 0b10001111;

    // Start inline program
    cpu.memory[0xFFFC] = TAX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAX_IP_CYCLES);

    ASSERT_EQ(cycles, TAX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0b10001111);

    ASSERT_TRUE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TAX_TEST, TAX_IP_TransferAccumulatorIntoXZero) {
    cpu.A = 0x00;

    // Start inline program
    cpu.memory[0xFFFC] = TAX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TAX_IP_CYCLES);

    ASSERT_EQ(cycles, TAX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0x00);

    ASSERT_FALSE(cpu.N);
    ASSERT_TRUE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
