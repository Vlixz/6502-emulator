extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class LDA_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~LDA_TEST() override { }
};

#define LDA_IMM_TEST 1
#define LDA_ZP0_TEST 1
#define LDA_ZPX_TEST 1
#define LDA_AB0_TEST 1
#define LDA_ABX_TEST 1
#define LDA_AB0_Y_TEST 1
#define LDA_INX_TEST 1
#define LDA_INY_TEST 1

#if LDA_IMM_TEST

TEST_F(LDA_TEST, LDA_IMM_LoadsCorrectValueIntoAccumulator) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IMM_OPCODE;
    cpu.memory[0xFFFD] = 0x42;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IMM_CYCLES);

    ASSERT_EQ(cycles, LDA_IMM_CYCLES);

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

TEST_F(LDA_TEST, LDA_IMM_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IMM_OPCODE;
    cpu.memory[0xFFFD] = -42; // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IMM_CYCLES);

    ASSERT_EQ(cycles, LDA_IMM_CYCLES);

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

TEST_F(LDA_TEST, LDA_IMM_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_IMM_OPCODE;
    cpu.memory[0xFFFD] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_IMM_CYCLES);

    ASSERT_EQ(cycles, LDA_IMM_CYCLES);

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

#endif // LDA_IMM_TEST

#if LDA_ZP0_TEST

TEST_F(LDA_TEST, LDA_ZP0_LoadsCorrectValueIntoAccumulator) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0xF4;
    cpu.memory[0x00F4] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZP0_CYCLES);

    ASSERT_EQ(cycles, LDA_ZP0_CYCLES);

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_ZP0_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0x0064] = -42; // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZP0_CYCLES);

    ASSERT_EQ(cycles, LDA_ZP0_CYCLES);

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

TEST_F(LDA_TEST, LDA_ZP0_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZP0_OPCODE;
    cpu.memory[0xFFFD] = 0x41;
    cpu.memory[0x0041] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZP0_CYCLES);

    ASSERT_EQ(cycles, LDA_ZP0_CYCLES);

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

#endif // LDA_ZP0_TEST

#if LDA_ZPX_TEST

TEST_F(LDA_TEST, LDA_ZPX_LoadsCorrectValueIntoAccumulator) {
    cpu.X = 0x10;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x56; // 0x56 + 0x10 = 0x66
    cpu.memory[0x0066] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZPX_CYCLES);

    ASSERT_EQ(cycles, LDA_ZPX_CYCLES);

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_ZPX_SetsNegativeFlag) {
    cpu.X = 0x1;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x64; // 0x64 + 0x1 = 0x65
    cpu.memory[0x0065] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZPX_CYCLES);

    ASSERT_EQ(cycles, LDA_ZPX_CYCLES);

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

TEST_F(LDA_TEST, LDA_ZPX_SetsZeroFlag) {
    cpu.X = 0xFF;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ZPX_OPCODE;
    cpu.memory[0xFFFD] = 0x80; // 0x80 + 0xFF = 0x17F (wrapps around so 0x7F)
    cpu.memory[0x007F] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ZPX_CYCLES);

    ASSERT_EQ(cycles, LDA_ZPX_CYCLES);

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

#endif // LDA_ZPX_TEST

#if LDA_AB0_TEST

TEST_F(LDA_TEST, LDA_AB0_LoadsCorrectValueIntoAccumulator) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_AB0_OPCODE;
    cpu.memory[0xFFFD] = 0x56;
    cpu.memory[0xFFFE] = 0xFF; // 0xFF56
    cpu.memory[0xFF56] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_AB0_CYCLES);

    ASSERT_EQ(cycles, LDA_AB0_CYCLES);

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_AB0_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_AB0_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0xFFFE] = 0x01; // 0x0164
    cpu.memory[0x0164] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_AB0_CYCLES);

    ASSERT_EQ(cycles, LDA_AB0_CYCLES);

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

TEST_F(LDA_TEST, LDA_AB0_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDA_AB0_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0xFFFE] = 0x00; // 0x0080
    cpu.memory[0x0080] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_AB0_CYCLES);

    ASSERT_EQ(cycles, LDA_AB0_CYCLES);

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

#endif // LDA_AB0_TEST

#if LDA_ABX_TEST

TEST_F(LDA_TEST, LDA_ABX_LoadsCorrectValueIntoAccumulator) {
    cpu.X = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABX_OPCODE;
    cpu.memory[0xFFFD] = 0xFF;
    cpu.memory[0xFFFE] = 0x20; // 0x20FF + 0x01 = 0x2100
    cpu.memory[0x2100] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABX_CYCLES);

    ASSERT_EQ(cycles,
              LDA_ABX_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_ABX_SetsNegativeFlag) {
    cpu.X = 0x28;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABX_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0xFFFE] = 0x01; // 0x0164 + 0x28 = 0x018C
    cpu.memory[0x018C] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABX_CYCLES);

    ASSERT_EQ(cycles, LDA_ABX_CYCLES);

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

TEST_F(LDA_TEST, LDA_ABX_SetsZeroFlag) {
    cpu.X = 0x80;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABX_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0xFFFE] = 0x00; // 0x0080 + 0x80 = 0x0100
    cpu.memory[0x0100] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABX_CYCLES);

    ASSERT_EQ(cycles,
              LDA_ABX_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

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

#endif // LDA_ABX_TEST

#if LDA_AB0_Y_TEST

TEST_F(LDA_TEST, LDA_AB0_Y_LoadsCorrectValueIntoAccumulator) {
    cpu.Y = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABY_OPCODE;
    cpu.memory[0xFFFD] = 0xFF;
    cpu.memory[0xFFFE] = 0x20; // 0x20FF + 0x01 = 0x2100
    cpu.memory[0x2100] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABY_CYCLES);

    ASSERT_EQ(cycles,
              LDA_ABY_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_AB0_Y_SetsNegativeFlag) {
    cpu.Y = 0x28;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABY_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0xFFFE] = 0x01; // 0x0164 + 0x28 = 0x018C
    cpu.memory[0x018C] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABY_CYCLES);

    ASSERT_EQ(cycles, LDA_ABY_CYCLES);

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

TEST_F(LDA_TEST, LDA_AB0_Y_SetsZeroFlag) {
    cpu.Y = 0x80;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_ABY_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0xFFFE] = 0x00; // 0x0080 + 0x80 = 0x0100
    cpu.memory[0x0100] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_ABY_CYCLES);

    ASSERT_EQ(cycles,
              LDA_ABY_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

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

#endif // LDA_AB0_Y_TEST

#if LDA_INX_TEST

TEST_F(LDA_TEST, LDA_INX_LoadsCorrectValueIntoAccumulator) {
    cpu.X = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INX_OPCODE;
    cpu.memory[0xFFFD] = 0x20; // 0x20 + 0x01 = 0x21
    cpu.memory[0x0021] = 0x56;
    cpu.memory[0x0022] = 0xFF; // 0xFF56
    cpu.memory[0xFF56] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INX_CYCLES);

    ASSERT_EQ(cycles, LDA_INX_CYCLES);

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_INX_SetsNegativeFlag) {
    cpu.X = 0x28;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INX_OPCODE;
    cpu.memory[0xFFFD] = 0x24; // 0x24 + 0x28 = 0x4C
    cpu.memory[0x004C] = 0x01;
    cpu.memory[0x004D] = 0x01; // 0x0101
    cpu.memory[0x0101] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INX_CYCLES);

    ASSERT_EQ(cycles, LDA_INX_CYCLES);

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

TEST_F(LDA_TEST, LDA_INX_SetsZeroFlag) {
    cpu.X = 0x80;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INX_OPCODE;
    cpu.memory[0xFFFD] = 0x00; // 0x00 + 0x80 = 0x80
    cpu.memory[0x0080] = 0xFF;
    cpu.memory[0x0081] = 0x43; // 0x43FF + 0x80 = 0x447F
    cpu.memory[0x447F] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INX_CYCLES);

    ASSERT_EQ(cycles, LDA_INX_CYCLES);

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

#endif // LDA_INX_TEST

#if LDA_INY_TEST

TEST_F(LDA_TEST, LDA_INY_LoadsCorrectValueIntoAccumulator) {
    cpu.Y = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INY_OPCODE;
    cpu.memory[0xFFFD] = 0x20;
    cpu.memory[0x0020] = 0x56;
    cpu.memory[0x0021] = 0xFF; // 0xFF56 + 0x01 = 0xFF57
    cpu.memory[0xFF57] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INY_CYCLES);

    ASSERT_EQ(cycles, LDA_INY_CYCLES);

    ASSERT_EQ(cpu.A, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDA_TEST, LDA_INY_SetsNegativeFlag) {
    cpu.Y = 0x28;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INY_OPCODE;
    cpu.memory[0xFFFD] = 0x19;
    cpu.memory[0x0019] = 0x01;
    cpu.memory[0x001A] = 0x01; // 0x0101 + 0x28 = 0x0129
    cpu.memory[0x0129] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INY_CYCLES);

    ASSERT_EQ(cycles, LDA_INY_CYCLES);

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

TEST_F(LDA_TEST, LDA_INY_SetsZeroFlag) {
    cpu.Y = 0x80;

    // Start inline program
    cpu.memory[0xFFFC] = LDA_INY_OPCODE;
    cpu.memory[0xFFFD] = 0x00; // 0x00 + 0x80 = 0x80
    cpu.memory[0x0000] = 0xFF;
    cpu.memory[0x0001] = 0x09; // 0x09FF + 0x80 = 0x0A7F
    cpu.memory[0x0A7F] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDA_INY_CYCLES);

    ASSERT_EQ(cycles,
              LDA_INY_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

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

#endif // LDA_INY_TEST
