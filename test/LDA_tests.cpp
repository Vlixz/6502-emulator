extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class LDA_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~LDA_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(LDA_TEST, LDA_IM_LoadsCorrectValueIntoAccumulator)
{
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IM_OPCODE;
    cpu.memory[0xFFFD] = 0x42;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IM_CYCLES);

    ASSERT_EQ(cycles, LDA_IM_CYCLES);

    ASSERT_EQ(cpu.A, 0x42);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_IM_SetsNegativeFlag)
{
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IM_OPCODE;
    cpu.memory[0xFFFD] = -42; // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IM_CYCLES);

    ASSERT_EQ(cycles, LDA_IM_CYCLES);

    ASSERT_EQ(cpu.A, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_IM_SetsZeroFlag)
{
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IM_OPCODE;
    cpu.memory[0xFFFD] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IM_CYCLES);

    ASSERT_EQ(cycles, LDA_IM_CYCLES);

    ASSERT_EQ(cpu.A, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}
