extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class TXA_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~TXA_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(TXA_TEST, TXA_IP_TransferXIntoAccumulator)
{
    cpu.X = 0x0F;

    // Start inline program
    cpu.memory[0xFFFC] = TXA_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TXA_IP_CYCLES);

    ASSERT_EQ(cycles, TXA_IP_CYCLES);

    ASSERT_EQ(cpu.A, 0x0F);

    ASSERT_FALSE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TXA_TEST, TXA_IP_TransferXIntoAccumulatorNegative)
{
    cpu.X = 0b10001111;

    // Start inline program
    cpu.memory[0xFFFC] = TXA_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TXA_IP_CYCLES);

    ASSERT_EQ(cycles, TXA_IP_CYCLES);

    ASSERT_EQ(cpu.A, 0b10001111);

    ASSERT_TRUE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(TXA_TEST, TXA_IP_TransferXIntoAccumulatorZero)
{
    cpu.X = 0x00;

    // Start inline program
    cpu.memory[0xFFFC] = TXA_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, TXA_IP_CYCLES);

    ASSERT_EQ(cycles, TXA_IP_CYCLES);

    ASSERT_EQ(cpu.A, 0x00);

    ASSERT_FALSE(cpu.N);
    ASSERT_TRUE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}