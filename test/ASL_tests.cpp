extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class ASL_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~ASL_TEST() override { }
};

#define ASL_AC_TEST 1
#define ASL_ZP_TEST 1
#define ASL_ZP_X_TEST 1
#define ASL_AB_TEST 1
#define ASL_AB_X_TEST 1

#if ASL_AC_TEST

TEST_F(ASL_TEST, ASL_AC_ShiftLeftNoCarry) {
    cpu.A = 0b01010101;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ACC_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ACC_CYCLES);

    ASSERT_EQ(cycles, ASL_ACC_CYCLES);

    ASSERT_EQ(cpu.A, 0b10101010);

    ASSERT_FALSE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_AC_ShiftLeftWithCarry) {
    cpu.A = 0b10001111;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ACC_OPCODE;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ACC_CYCLES);

    ASSERT_EQ(cycles, ASL_ACC_CYCLES);

    ASSERT_EQ(cpu.A, 0b00011110);

    ASSERT_TRUE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* ASL_AC_TEST */

#if ASL_ZP_TEST

TEST_F(ASL_TEST, ASL_ZP_ShiftLeftNoCarry) {
    // Start inline program
    cpu.memory[0xFFFC] = ASL_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0xF9;
    cpu.memory[0x00F9] = 0b01001111;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ZP0_CYCLES);

    ASSERT_EQ(cycles, ASL_ZP0_CYCLES);

    ASSERT_EQ(cpu.memory[0x00F9], 0b10011110);

    ASSERT_FALSE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_ZP_ShiftLeftWithCarry) {
    // Start inline program
    cpu.memory[0xFFFC] = ASL_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0xF9;
    cpu.memory[0x00F9] = 0b10001111;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ZP0_CYCLES);

    ASSERT_EQ(cycles, ASL_ZP0_CYCLES);

    ASSERT_EQ(cpu.memory[0x00F9], 0b00011110);

    ASSERT_TRUE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* ASL_ZP_TEST */

#if ASL_ZP_X_TEST

TEST_F(ASL_TEST, ASL_ZP_X_ShiftLeftNoCarry) {
    cpu.X = 0xFF;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0x007F] = 0b00110011;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ZPX_CYCLES);

    ASSERT_EQ(cycles, ASL_ZPX_CYCLES);

    ASSERT_EQ(cpu.memory[0x007F], 0b01100110);

    ASSERT_FALSE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_ZP_X_ShiftLeftWithCarry) {
    cpu.X = 0xFF;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0x007F] = 0b10110011;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ZPX_CYCLES);

    ASSERT_EQ(cycles, ASL_ZPX_CYCLES);

    ASSERT_EQ(cpu.memory[0x007F], 0b01100110);

    ASSERT_TRUE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* ASL_ZP_X_TEST */

#if ASL_AB_TEST

TEST_F(ASL_TEST, ASL_AB_ShiftLeftNoCarry) {
    Word AbsoluteAddress = 0x7849;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_AB0_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b01010101;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_AB0_CYCLES);

    ASSERT_EQ(cycles, ASL_AB0_CYCLES);

    ASSERT_EQ(cpu.memory[AbsoluteAddress], 0b10101010);

    ASSERT_FALSE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_AB_ShiftLeftWithCarry) {
    Word AbsoluteAddress = 0x7849;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_AB0_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b11010101;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_AB0_CYCLES);

    ASSERT_EQ(cycles, ASL_AB0_CYCLES);

    ASSERT_EQ(cpu.memory[AbsoluteAddress], 0b10101010);

    ASSERT_TRUE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_AB_ShiftLeftWithCarryNegative) {
    Word AbsoluteAddress = 0x7849;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_AB0_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b10000000;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_AB0_CYCLES);

    ASSERT_EQ(cycles, ASL_AB0_CYCLES);

    ASSERT_EQ(cpu.memory[AbsoluteAddress], 0b00000000);

    ASSERT_TRUE(cpu.C);
    ASSERT_TRUE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* ASL_AB_TEST */

#if ASL_AB_X_TEST

TEST_F(ASL_TEST, ASL_AB_X_ShiftLeftNoCarry) {
    cpu.X = 0x09;

    Word AbsoluteAddress = 0x09F0;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ABX_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x09F9] = 0b01001000;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ABX_CYCLES);

    ASSERT_EQ(cycles, ASL_ABX_CYCLES);

    ASSERT_EQ(cpu.memory[0x09F9], 0b10010000);

    ASSERT_FALSE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_TRUE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(ASL_TEST, ASL_AB_X_ShiftLeftWithCarry) {
    cpu.X = 0x09;

    Word AbsoluteAddress = 0x09FF;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = ASL_ABX_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[0x0A08] = 0b10010001;
    // End inline program

    int cycles = em6502_execute(&cpu, ASL_ABX_CYCLES);

    ASSERT_EQ(cycles, ASL_ABX_CYCLES + 1);

    ASSERT_EQ(cpu.memory[0x0A08], 0b00100010);

    ASSERT_TRUE(cpu.C);
    ASSERT_FALSE(cpu.Z);
    ASSERT_FALSE(cpu.N);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* ASL_AB_X_TEST */
