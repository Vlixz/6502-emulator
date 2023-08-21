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

#define BIT_ZP_TEST 1
#define BIT_AB_TEST 1

#if BIT_ZP_TEST

TEST_F(BIT_TEST, BIT_ZP_CheckBitSixNoVNoN)
{
    // A: 0010 0111
    // M: 0010 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x0011;
    cpu.memory[0x0011] = 0b00100000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_ZP_CYCLES);

    ASSERT_EQ(cycles, BIT_ZP_CYCLES);

    ASSERT_FALSE(cpu.Z);

    ASSERT_EQ(cpu.V, 0);
    ASSERT_EQ(cpu.N, 0);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BIT_TEST, BIT_ZP_CheckBitSixVAndN)
{
    // A: 0010 0111
    // M: 1110 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x0011;
    cpu.memory[0x0011] = 0b11100000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_ZP_CYCLES);

    ASSERT_EQ(cycles, BIT_ZP_CYCLES);

    ASSERT_FALSE(cpu.Z);

    ASSERT_EQ(cpu.V, 1);
    ASSERT_EQ(cpu.N, 1);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BIT_TEST, BIT_ZP_CheckBitZero)
{
    // A: 0010 0111
    // M: 0100 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x0011;
    cpu.memory[0x0011] = 0b01000000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_ZP_CYCLES);

    ASSERT_EQ(cycles, BIT_ZP_CYCLES);

    ASSERT_TRUE(cpu.Z);

    ASSERT_EQ(cpu.V, 1);
    ASSERT_EQ(cpu.N, 0);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* BIT_ZP_TEST */

#if BIT_AB_TEST

TEST_F(BIT_TEST, BIT_AB_CheckBitSixNoVNoN)
{
    // A: 0010 0111
    // M: 0010 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    Word AbsoluteAddress = 0xFF11;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_AB_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b00100000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_AB_CYCLES);

    ASSERT_EQ(cycles, BIT_AB_CYCLES);

    ASSERT_FALSE(cpu.Z);

    ASSERT_EQ(cpu.V, 0);
    ASSERT_EQ(cpu.N, 0);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BIT_TEST, BIT_AB_CheckBitSixVAndN)
{
    // A: 0010 0111
    // M: 1110 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    Word AbsoluteAddress = 0x7683;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_AB_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b11100000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_AB_CYCLES);

    ASSERT_EQ(cycles, BIT_AB_CYCLES);

    ASSERT_FALSE(cpu.Z);

    ASSERT_EQ(cpu.V, 1);
    ASSERT_EQ(cpu.N, 1);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

TEST_F(BIT_TEST, BIT_AB_CheckBitZero)
{
    // A: 0010 0111
    // M: 0100 0000
    // R: 0010 0000

    cpu.A = 0b00100111;

    Word AbsoluteAddress = 0xFDEF;

    Byte LSB = AbsoluteAddress & BIT_MASK_FIRST_BYTE;
    Byte MSB = AbsoluteAddress >> 8;

    // Start inline program
    cpu.memory[0xFFFC] = BIT_AB_OPCODE;
    cpu.memory[0xFFFD] = LSB;
    cpu.memory[0xFFFE] = MSB;
    cpu.memory[AbsoluteAddress] = 0b01000000; // Bit mask
    // End inline program

    int cycles = em6502_execute(&cpu, BIT_AB_CYCLES);

    ASSERT_EQ(cycles, BIT_AB_CYCLES);

    ASSERT_TRUE(cpu.Z);

    ASSERT_EQ(cpu.V, 1);
    ASSERT_EQ(cpu.N, 0);

    /* Make sure the rest are unaffected by the instruction */
    ASSERT_EQ(cpu.C, CARRY_FLAG_RESET_VALUE);
    ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
    ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
    ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
}

#endif /* BIT_AB_TEST */