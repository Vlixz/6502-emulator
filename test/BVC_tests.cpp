extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class BVC_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~BVC_TEST() override { }
};

TEST_F(BVC_TEST, BVC_REL_OverflowNotClearNoBranch) {
    cpu.V = 1;

    // Start inline program
    cpu.memory[0xFFFC] = BVC_REL_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    // End inline program

    int cycles = em6502_execute(&cpu, BVC_REL_CYCLES);

    ASSERT_EQ(cycles, BVC_REL_CYCLES);

    ASSERT_EQ(cpu.PC, 0xFFFE);

    ASSERT_TRUE(cpu.V);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BVC_TEST, BVC_REL_OverflowflowClearSetBranchJumpOneByteToNewPage) {
    cpu.V = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BVC_REL_OPCODE;
    cpu.memory[0xFFFD] = 0x02;          // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00;          // skipped
    cpu.memory[0xFFFF] = 0x00;          // skipped
    cpu.memory[0x0000] = BVC_REL_OPCODE; // next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, BVC_REL_CYCLES);

    ASSERT_EQ(cycles, BVC_REL_CYCLES + 2);

    ASSERT_EQ(cpu.PC, 0x0000);

    ASSERT_FALSE(cpu.V);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BVC_TEST, BVC_REL_OverflowflowClearSetBranchJumpOneByteNoNewPage) {
    cpu.V = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BVC_REL_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00; // skipped
    cpu.memory[0xFFFF] = 0x00; // skipped
    cpu.memory[0x0000] =
        BVC_REL_OPCODE; // Run instruction again without going to a new page
    cpu.memory[0x0001] = 0x02;          // Jump 2 bytes
    cpu.memory[0x0002] = 0x00;          // skipped
    cpu.memory[0x0003] = 0x00;          // skipped
    cpu.memory[0x0004] = BVC_REL_OPCODE; // Next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, (BVC_REL_CYCLES + 2) + BVC_REL_CYCLES);

    cycles -= BVC_REL_CYCLES +
              2; // Remove the cycles which are used to jump the PC to 0x0001

    ASSERT_EQ(cycles, BVC_REL_CYCLES + 1);

    ASSERT_EQ(cpu.PC, 0x0004);

    ASSERT_FALSE(cpu.V);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
