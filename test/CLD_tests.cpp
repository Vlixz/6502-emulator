extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class CLD_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~CLD_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(CLD_TEST, CLD_IP_DecimalFlagCleared)
{
    cpu.D = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLD_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, CLD_IP_CYCLES);

    ASSERT_EQ(cycles, CLD_IP_CYCLES);

    ASSERT_FALSE(cpu.D);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(CLD_TEST, CLD_IP_DoesNotChangeClearedDecimalFlag)
{
    cpu.D = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLD_IP_OPCODE;
    cpu.memory[0xFFFE] = CLD_IP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, CLD_IP_CYCLES * 2);

    ASSERT_EQ(cycles, CLD_IP_CYCLES * 2);

    ASSERT_FALSE(cpu.D);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
