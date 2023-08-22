extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class BPL_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~BPL_TEST() override
    {
        em6502_destroy(&cpu);
    }
};

TEST_F(BPL_TEST, BPL_TEST_NegativeFlagSetNoBranch)
{
    cpu.N = 1;

    // Start inline program
    cpu.memory[0xFFFC] = BPL_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    // End inline program

    int cycles = em6502_execute(&cpu, BPL_RE_CYCLES);

    ASSERT_EQ(cycles, BPL_RE_CYCLES);

    ASSERT_EQ(cpu.PC, 0xFFFE);

    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BPL_TEST, BPL_RE_NoNegativeFlagSetBranchJumpTwoBytesAndToANewPage)
{
    cpu.N = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BPL_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02;          // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00;          // skipped
    cpu.memory[0xFFFF] = 0x00;          // skipped
    cpu.memory[0x0000] = BPL_RE_OPCODE; // next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, BPL_RE_CYCLES);

    ASSERT_EQ(cycles, BPL_RE_CYCLES + 2);

    ASSERT_EQ(cpu.PC, 0x0000);

    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BPL_TEST, BPL_RE_NoZeroFlagSetBranchJumpOneByteNoNewPage)
{
    cpu.N = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BPL_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02;          // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00;          // skipped
    cpu.memory[0xFFFF] = 0x00;          // skipped
    cpu.memory[0x0001] = BPL_RE_OPCODE; // Run instruction again without going to a new page
    cpu.memory[0x0002] = 0x02;          // Jump 2 bytes
    cpu.memory[0x0003] = 0x00;          // skipped
    cpu.memory[0x0004] = 0x00;          // skipped
    cpu.memory[0x0005] = BPL_RE_OPCODE; // Next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, (BPL_RE_CYCLES + 2) + BPL_RE_CYCLES);

    cycles -= BPL_RE_CYCLES + 2; // Remove the cycles which are used to jump the PC to 0x0001

    ASSERT_EQ(cycles, BPL_RE_CYCLES + 1);

    ASSERT_EQ(cpu.PC, 0x0005);

    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
