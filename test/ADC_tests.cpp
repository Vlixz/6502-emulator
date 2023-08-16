extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

#define TEST_ADC_IM 0
#define TEST_ADC_ZP 0
#define TEST_ADC_ZP_X 1
/**
 *
 * ADC_IM is tested completely (all flags are tested),
 * The different addressing modes are only tested on the addressing part (the function of the instruction is the same and uses the same inline code)
 *
 */

#if TEST_ADC_IM

/**
 * ADC_IM
 *
 * Test: Adding without carry bit & No Overflow
 */
TEST(ADC_IM_NoCarryNoOverflow, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 5; // 5 + 10

    // Start inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 10;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 15);

    ASSERT_FALSE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_FALSE(cpu.NF);
}

/**
 * ADC_IM
 *
 * Test: Adding with carry bit & No Overflow
 */
TEST(ADC_IM_WithCarryNoOverflow, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 5; // 5 + 10

    // Start inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 0xFF;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 4);

    ASSERT_TRUE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_FALSE(cpu.NF);
}

/**
 * ADC_IM
 *
 * Test: Adding without carry bit & Overflow
 */
TEST(ADC_IM_NoCarryWithOverflow, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 1; // 5 + 10

    // Start inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 0b01111111;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 128);

    ASSERT_FALSE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);

    ASSERT_TRUE(cpu.OF);
    ASSERT_TRUE(cpu.NF);
}

/**
 * ADC_IM
 *
 * Test: Zero Flag
 */
TEST(ADC_IM_ZeroFlag, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 0; // 5 + 10

    // Start inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 0;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 0);

    ASSERT_FALSE(cpu.CF);
    ASSERT_TRUE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_FALSE(cpu.NF);
}

/**
 * ADC_IM
 *
 * Test: Negative Flag
 */
TEST(ADC_IM_NegativeFlag, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 0b11111111; // -1

    // Start inline program
    cpu.memory[0xFFFC] = ADC_IM_OPCODE;
    cpu.memory[0xFFFD] = 0b11111011; // -5
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 0b11111010); // -6

    ASSERT_TRUE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_TRUE(cpu.NF);
}

#endif /* TEST_ADC_IM*/

#if TEST_ADC_ZP

/**
 * ADC_ZP
 *
 * Test: Adding without carry bit & No Overflow
 */
TEST(ADC_ZP_NoCarryNoOverflow, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 5; // 5

    // Start inline program
    cpu.memory[0xFFFC] = ADC_ZP_OPCODE;
    cpu.memory[0xFFFD] = 0x10; // Memory address of zero page
    cpu.memory[0x0010] = 10;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 15);

    ASSERT_FALSE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_FALSE(cpu.NF);
}

#endif /* TEST_ADC_ZP */

#if TEST_ADC_ZP_X

/**
 * ADC_ZP_X
 *
 * Test: Adding without carry bit & No Overflow
 */
TEST(ADC_ZP_X_NoCarryNoOverflow, BasicAssertions)
{
    CPU_6502 cpu;

    reset_6502(&cpu);

    cpu.AC = 5;   // 5
    cpu.X = 0x80; // Added to the specified Zero Page address in the instruction

    // Start inline program
    cpu.memory[0xFFFC] = ADC_ZP_X_OPCODE;
    cpu.memory[0xFFFD] = 0xFF; // Memory address of zero page
    cpu.memory[0x007F] = 10;
    // End inline program

    execute_6502(&cpu, ADC_IM_CYCLES);

    ASSERT_EQ(cpu.AC, 15);

    ASSERT_FALSE(cpu.CF);
    ASSERT_FALSE(cpu.ZF);
    ASSERT_FALSE(cpu.ID);
    ASSERT_FALSE(cpu.DM);
    ASSERT_FALSE(cpu.BC);
    ASSERT_FALSE(cpu.OF);
    ASSERT_FALSE(cpu.NF);
}

#endif /* TEST_ADC_ZP_X */