extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class DEX_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~DEX_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(DEX_TEST, DEX_IP_DecrementsXZeroNonNegative)
{
    cpu.X = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = DEX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEX_IP_CYCLES);

    ASSERT_EQ(cycles, DEX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0x00);
    ASSERT_TRUE(cpu.Z);
    ASSERT_FALSE(cpu.N);


    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(DEX_TEST, DEX_IP_DecrementsXNonZeroNegative)
{
    cpu.X = 0x00;

    // Start inline program
    cpu.memory[0xFFFC] = DEX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEX_IP_CYCLES);

    ASSERT_EQ(cycles, DEX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0xFF);
    ASSERT_TRUE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(DEX_TEST, DEX_IP_DecrementsXNonZeroNonNegative)
{
    cpu.X = 0x02;

    // Start inline program
    cpu.memory[0xFFFC] = DEX_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, DEX_IP_CYCLES);

    ASSERT_EQ(cycles, DEX_IP_CYCLES);

    ASSERT_EQ(cpu.X, 0x01);
    ASSERT_FALSE(cpu.N);
    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}