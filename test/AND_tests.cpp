extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class AND_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~AND_TEST() override { }
};

#define AND_IMM_TEST 1
#define AND_ZP0_TEST 1
#define AND_ZP0_X_TEST 1
#define AND_AB_TEST 1
#define AND_ABX_TEST 1
#define AND_ABY_TEST 1
#define AND_IN_X_TEST 1
#define AND_IN_Y_TEST 1

#if AND_IMM_TEST

TEST_F(AND_TEST, AND_IMM_LogicalAndNoNegative) {
    cpu.A = 0xF0;

    // Start inline program
    cpu.memory[0xFFFC] = AND_IMM_OPCODE;
    cpu.memory[0xFFFD] = 0x40;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_IMM_CYCLES);

    ASSERT_EQ(cycles, AND_IMM_CYCLES);

    ASSERT_EQ(cpu.A, 0x40);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(AND_TEST, AND_IMM_LogicalAndNegative) {
    cpu.A = 0xF0;

    // Start inline program
    cpu.memory[0xFFFC] = AND_IMM_OPCODE;
    cpu.memory[0xFFFD] = 0xF0;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_IMM_CYCLES);

    ASSERT_EQ(cycles, AND_IMM_CYCLES);

    ASSERT_EQ(cpu.A, 0xF0);

    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(AND_TEST, AND_IMM_LogicalAndZero) {
    cpu.A = 0xF0;

    // Start inline program
    cpu.memory[0xFFFC] = AND_IMM_OPCODE;
    cpu.memory[0xFFFD] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_IMM_CYCLES);

    ASSERT_EQ(cycles, AND_IMM_CYCLES);

    ASSERT_EQ(cpu.A, 0x00);

    ASSERT_TRUE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_IMM_TEST */

#if AND_ZP0_TEST

TEST_F(AND_TEST, AND_ZP0_LogicalAnd) {
    cpu.A = 0x0F;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0xF9;
    cpu.memory[0x00F9] = 0x01;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ZP0_CYCLES);

    ASSERT_EQ(cycles, AND_ZP0_CYCLES);

    ASSERT_EQ(cpu.A, 0x01);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_ZP0_TEST */

#if AND_ZP0_X_TEST

TEST_F(AND_TEST, AND_ZP0_X_LogicalAnd) {
    cpu.A = 0x07;
    cpu.X = 0xFF;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0x007F] = 0x06;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ZPX_CYCLES);

    ASSERT_EQ(cycles, AND_ZPX_CYCLES);

    ASSERT_EQ(cpu.A, 0x06);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_ZP0_TEST */

#if AND_AB_TEST

TEST_F(AND_TEST, AND_AB_LogicalAnd) {
    cpu.A = 0x76;

    Word AbsoluteAddress = 0x7849;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_AB0_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0xF9;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_AB0_CYCLES);

    ASSERT_EQ(cycles, AND_AB0_CYCLES);

    ASSERT_EQ(cpu.A, 0x70);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_AB_TEST */

#if AND_ABX_TEST

TEST_F(AND_TEST, AND_ABX_LogicalAndNoExtraCycles) {
    cpu.A = 0x87;
    cpu.X = 0x09;

    Word AbsoluteAddress = 0x09F0;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ABX_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x09F9] = 0xFF;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ABX_CYCLES);

    ASSERT_EQ(cycles, AND_ABX_CYCLES);

    ASSERT_EQ(cpu.A, 0x87);

    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(AND_TEST, AND_ABX_LogicalAndExtraCycles) {
    cpu.A = 0x87;
    cpu.X = 0x09;

    Word AbsoluteAddress = 0x09FF;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ABX_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x0A08] = 0xFF;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ABX_CYCLES);

    ASSERT_EQ(cycles, AND_ABX_CYCLES + 1);

    ASSERT_EQ(cpu.A, 0x87);

    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_ABX_TEST */

#if AND_ABY_TEST

TEST_F(AND_TEST, AND_ABY_LogicalAndNoExtraCycles) {
    cpu.A = 0x87;
    cpu.Y = 0x09;

    Word AbsoluteAddress = 0x09F0;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ABY_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x09F9] = 0xFF;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ABY_CYCLES);

    ASSERT_EQ(cycles, AND_ABY_CYCLES);

    ASSERT_EQ(cpu.A, 0x87);

    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(AND_TEST, AND_ABY_LogicalAndExtraCycles) {
    cpu.A = 0x87;
    cpu.Y = 0x09;

    Word AbsoluteAddress = 0x09FF;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_ABY_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x0A08] = 0xFF;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_ABY_CYCLES);

    ASSERT_EQ(cycles, AND_ABY_CYCLES + 1);

    ASSERT_EQ(cpu.A, 0x87);

    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_ABY_TEST */

#if AND_IN_X_TEST

TEST_F(AND_TEST, AND_IN_X_LogicalAnd) {
    cpu.A = 0x16;
    cpu.X = 0x01;

    Word AbsoluteAddress = 0x7693;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_INX_OPCODE;
    cpu.memory[0xFFFD] = 0x00F9;

    cpu.memory[0x00FA] = LSB;
    cpu.memory[0x00FA + 1] = MSB;

    cpu.memory[0x7693] = 0xF0;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_INX_CYCLES);

    ASSERT_EQ(cycles, AND_INX_CYCLES);

    ASSERT_EQ(cpu.A, 0x10);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* AND_IN_X_TEST */

#if AND_IN_Y_TEST

TEST_F(AND_TEST, AND_IN_Y_LogicalAndNoExtraCycles) {
    cpu.A = 0x65;
    cpu.Y = 0x89;

    Word AbsoluteAddress = 0x900F;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_INY_OPCODE;
    cpu.memory[0xFFFD] = 0xF9;

    cpu.memory[0xF9] = LSB;
    cpu.memory[0xF9 + 1] = MSB;

    cpu.memory[0x9098] = 0xF0;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_INY_CYCLES);

    ASSERT_EQ(cycles, AND_INY_CYCLES);

    ASSERT_EQ(cpu.A, 0x60);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(AND_TEST, AND_IN_Y_LogicalAndExtraCycles) {
    cpu.A = 0x65;
    cpu.Y = 0x01;

    Word AbsoluteAddress = 0x90FF;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = AND_INY_OPCODE;
    cpu.memory[0xFFFD] = 0xF9;

    cpu.memory[0xF9] = LSB;
    cpu.memory[0xF9 + 1] = MSB;

    cpu.memory[0x9100] = 0xF0;
    // End inline program

    int cycles = em6502_execute(&cpu, AND_INY_CYCLES);

    ASSERT_EQ(cycles, AND_INY_CYCLES + 1);

    ASSERT_EQ(cpu.A, 0x60);

    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}
#endif /* AND_IN_Y_TEST */
