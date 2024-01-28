extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class BMI_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~BMI_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(BMI_TEST, BMI_RE_NoNegativeFlagSetNoBranch) {
    cpu.N = 0;

    // Start inline program
    cpu.memory[0xFFFC] = BMI_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    // End inline program

    int cycles = em6502_execute(&cpu, BMI_RE_CYCLES);

    ASSERT_EQ(cycles, BMI_RE_CYCLES);

    ASSERT_EQ(cpu.PC, 0xFFFE);

    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BMI_TEST, BMI_RE_NegativeFlagSetBranchJumpTwoBytesAndToANewPage) {
    cpu.N = 1;

    // Start inline program
    cpu.memory[0xFFFC] = BMI_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02;          // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00;          // skipped
    cpu.memory[0xFFFF] = 0x00;          // skipped
    cpu.memory[0x0000] = BMI_RE_OPCODE; // next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, BMI_RE_CYCLES);

    ASSERT_EQ(cycles, BMI_RE_CYCLES + 2);

    ASSERT_EQ(cpu.PC, 0x0000);

    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BMI_TEST, BMI_RE_NegativeFlagSetBranchJumpOneByteNoNewPage) {
    cpu.N = 1;

    // Start inline program
    cpu.memory[0xFFFC] = BMI_RE_OPCODE;
    cpu.memory[0xFFFD] = 0x02; // Jump 2 bytes
    cpu.memory[0xFFFE] = 0x00; // skipped
    cpu.memory[0xFFFF] = 0x00; // skipped
    cpu.memory[0x0000] =
        BMI_RE_OPCODE; // Run instruction again without going to a new page
    cpu.memory[0x0001] = 0x02;          // Jump 2 bytes
    cpu.memory[0x0002] = 0x00;          // skipped
    cpu.memory[0x0003] = 0x00;          // skipped
    cpu.memory[0x0004] = BMI_RE_OPCODE; // Next instruction
    // End inline program

    int cycles = em6502_execute(&cpu, (BMI_RE_CYCLES + 2) + BMI_RE_CYCLES);

    cycles -= BMI_RE_CYCLES +
              2; // Remove the cycles which are used to jump the PC to 0x0001

    ASSERT_EQ(cycles, BMI_RE_CYCLES + 1);

    ASSERT_EQ(cpu.PC, 0x0004);

    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
