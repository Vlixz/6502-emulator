extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class CLV_TEST : public ::testing::Test {
  protected:
    CPU_6502 cpu;

    void SetUp() override { em6502_reset(&cpu); }

    ~CLV_TEST() override { em6502_destroy(&cpu); }
};

TEST_F(CLV_TEST, CLV_IP_OverflowFlagCleared) {
    cpu.V = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLV_IP_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, CLV_IP_CYCLES);

    ASSERT_EQ(cycles, CLV_IP_CYCLES);

    ASSERT_FALSE(cpu.V);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(CLV_TEST, CLV_IP_DoesNotChangeClearedOverflowFlag) {
    cpu.V = 1;

    // Start inline program
    cpu.memory[0xFFFC] = CLV_IP_OPCODE;
    cpu.memory[0xFFFE] = CLV_IP_OPCODE; // Run instruction again
    // End inline program

    int cycles = em6502_execute(&cpu, CLV_IP_CYCLES * 2);

    ASSERT_EQ(cycles, CLV_IP_CYCLES * 2);

    ASSERT_FALSE(cpu.V);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.N, NEGATIVE_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.Z, ZERO_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
