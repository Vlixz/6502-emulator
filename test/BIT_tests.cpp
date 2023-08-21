extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class BIT_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~BIT_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(BIT_TEST, BEQ_RE_NoZeroFlagSetNoBranch)
{
    cpu.Z = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BEQ_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    // End inline program

    int cycles = em6502_execute(&cpu, BEQ_RE_CYCLES);

    ASSERT_EQ(cycles, BEQ_RE_CYCLES);

    ASSERT_EQ(cpu.PC, 0xFFFE);

    ASSERT_FALSE(cpu.Z);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
