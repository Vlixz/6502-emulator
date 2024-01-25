#include "common.h"
extern "C" {
#include "6502.h"
}

#include <gtest/gtest.h>

class LDY_TEST : public ::testing::Test {
  protected:
    CPU_6502 cpu;

    void SetUp() override { em6502_reset(&cpu); }

    ~LDY_TEST() override { em6502_destroy(&cpu); }
};

#define LDY_IM_TEST 1
#define LDY_ZP_TEST 1
#define LDY_ZP_X_TEST 1
#define LDY_AB_TEST 1
#define LDY_AB_X_TEST 1

#if LDY_IM_TEST

TEST_F(LDY_TEST, LDY_IM_LoadsCorrectValueIntoYRegister) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_IM_OPCODE;
    cpu.memory[0xFFFD] = 0x42;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_IM_CYCLES);

    ASSERT_EQ(cycles, LDY_IM_CYCLES);

    ASSERT_EQ(cpu.Y, 0x42);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_IM_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_IM_OPCODE;
    cpu.memory[0xFFFD] = -42; // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_IM_CYCLES);

    ASSERT_EQ(cycles, LDY_IM_CYCLES);

    ASSERT_EQ(cpu.Y, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_IM_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_IM_OPCODE;
    cpu.memory[0xFFFD] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_IM_CYCLES);

    ASSERT_EQ(cycles, LDY_IM_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

#endif // LDY_IM_TEST

#if LDY_ZP_TEST

TEST_F(LDY_TEST, LDY_ZP_LoadsCorrectValueIntoYRegister) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0xF4;
    cpu.memory[0x00F4] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_CYCLES);

    ASSERT_EQ(cycles, LDY_ZP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_ZP_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0x0064] = -42; // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_CYCLES);

    ASSERT_EQ(cycles, LDY_ZP_CYCLES);

    ASSERT_EQ(cpu.Y, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_ZP_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x41;
    cpu.memory[0x0041] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_CYCLES);

    ASSERT_EQ(cycles, LDY_ZP_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

#endif // LDY_ZP_TEST

#if LDY_ZP_X_TEST

TEST_F(LDY_TEST, LDY_ZP_X_LoadsCorrectValueIntoYRegister) {
    cpu.X = 0x10;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_X_OPCODE;
    cpu.memory[0xFFFD] = 0x56; // 0x56 + 0x10 = 0x66
    cpu.memory[0x0066] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_X_CYCLES);

    ASSERT_EQ(cycles, LDY_ZP_X_CYCLES);

    ASSERT_EQ(cpu.Y, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_ZP_X_SetsNegativeFlag) {
    cpu.X = 0x1;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_X_OPCODE;
    cpu.memory[0xFFFD] = 0x64; // 0x64 + 0x1 = 0x65
    cpu.memory[0x0065] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_X_OPCODE);

    ASSERT_EQ(cycles, LDY_ZP_X_OPCODE);

    ASSERT_EQ(cpu.Y, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_ZP_X_SetsZeroFlag) {
    cpu.X = 0xFF;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_ZP_X_OPCODE;
    cpu.memory[0xFFFD] = 0x80; // 0x80 + 0xFF = 0x17F (wrapps around so 0x7F)
    cpu.memory[0x007F] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_ZP_X_CYCLES);

    ASSERT_EQ(cycles, LDY_ZP_X_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

#endif // LDX_ZP_Y_TEST

#if LDY_AB_TEST

TEST_F(LDY_TEST, LDY_AB_LoadsCorrectValueIntoYRegister) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_OPCODE;
    cpu.memory[0xFFFD] = 0x56;
    cpu.memory[0xFFFE] = 0xFF; // 0xFF56
    cpu.memory[0xFF56] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_CYCLES);

    ASSERT_EQ(cycles, LDY_AB_CYCLES);

    ASSERT_EQ(cpu.Y, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_AB_SetsNegativeFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0xFFFE] = 0x01; // 0x0164
    cpu.memory[0x0164] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_CYCLES);

    ASSERT_EQ(cycles, LDY_AB_CYCLES);

    ASSERT_EQ(cpu.Y, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_AB_SetsZeroFlag) {
    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0xFFFE] = 0x00; // 0x0080
    cpu.memory[0x0080] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_CYCLES);

    ASSERT_EQ(cycles, LDY_AB_CYCLES);

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

#endif // LDY_AB_TEST

#if LDY_AB_X_TEST

TEST_F(LDY_TEST, LDY_AB_Y_LoadsCorrectValueIntoYRegister) {
    cpu.X = 0x01;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_X_OPCODE;
    cpu.memory[0xFFFD] = 0xFF;
    cpu.memory[0xFFFE] = 0x20; // 0x20FF + 0x01 = 0x2100
    cpu.memory[0x2100] = 0x65;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_X_CYCLES);

    ASSERT_EQ(cycles,
              LDY_AB_X_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

    ASSERT_EQ(cpu.Y, 0x65);

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_AB_X_SetsNegativeFlag) {
    cpu.X = 0x28;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_X_OPCODE;
    cpu.memory[0xFFFD] = 0x64;
    cpu.memory[0xFFFE] = 0x01; // 0x0164 + 0x28 = 0x018C
    cpu.memory[0x018C] = -42;  // 0xD6 (two compliment)
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_X_CYCLES);

    ASSERT_EQ(cycles, LDY_AB_X_CYCLES);

    ASSERT_EQ(cpu.Y, (unsigned char)-42); // 0xD6 (two compliment)

    ASSERT_EQ(cpu.Z, false);
    ASSERT_EQ(cpu.N, true);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

TEST_F(LDY_TEST, LDY_AB_X_SetsZeroFlag) {
    cpu.X = 0x80;

    // Start inline program
    cpu.memory[0xFFFC] = LDY_AB_X_OPCODE;
    cpu.memory[0xFFFD] = 0x80;
    cpu.memory[0xFFFE] = 0x00; // 0x0080 + 0x80 = 0x0100
    cpu.memory[0x0100] = 0x00;
    // End inline program

    int cycles = em6502_execute(&cpu, LDY_AB_X_CYCLES);

    ASSERT_EQ(cycles,
              LDY_AB_X_CYCLES +
                  1); // Takes an extra cycle if page boundary is crossed

    ASSERT_EQ(cpu.Y, 0x00);

    ASSERT_EQ(cpu.Z, true);
    ASSERT_EQ(cpu.N, false);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.V, OVERFLOW_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
}

#endif // LDY_AB_X_TEST
