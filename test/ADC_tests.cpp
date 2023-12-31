extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class ADC_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~ADC_TEST() override
    {
        em6502_destroy(&cpu);
    }

    struct ADC_TestCase
    {
        /* Input */
        bool C; // Carry Value
        Byte A; // Accumulator value
        Byte O; // Operator value

        /* Expected outcome */
        Byte ExpectedA; // Expected accumulator value
        bool ExpectedZ; // Expected Zero Flag
        bool ExpectedV; // Expected Overflow Flag
        bool ExpectedN; // Expected Negative Flag
        bool ExpectedC; // Expected Carry Flag

        int expectedCycles;

        Word Address;
        Word ExpectedAddress;

        Byte ZeroPageAddress;
        Word IndirectAddress;

        Byte X;
        Byte Y;
    };

    void ADC_IM_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_IM_OPCODE;
        cpu.memory[0xFFFD] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_IM_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_ZP_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_ZP_OPCODE;
        cpu.memory[0xFFFD] = testCase.Address;
        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_ZP_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_ZP_X_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;
        cpu.X = testCase.X;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_ZP_X_OPCODE;
        cpu.memory[0xFFFD] = testCase.Address;
        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_ZP_X_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_AB_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;

        Byte LSB = testCase.Address & BIT_MASK_FIRST_BYTE;
        Byte MSB = testCase.Address >> 8;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_AB_OPCODE;
        cpu.memory[0xFFFD] = LSB;
        cpu.memory[0xFFFE] = MSB;
        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_AB_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_AB_X_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;
        cpu.X = testCase.X;

        Byte LSB = testCase.Address & BIT_MASK_FIRST_BYTE;
        Byte MSB = testCase.Address >> 8;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_AB_X_OPCODE;
        cpu.memory[0xFFFD] = LSB;
        cpu.memory[0xFFFE] = MSB;
        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_AB_X_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_AB_Y_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;
        cpu.Y = testCase.Y;

        Byte LSB = testCase.Address & BIT_MASK_FIRST_BYTE;
        Byte MSB = testCase.Address >> 8;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_AB_Y_OPCODE;
        cpu.memory[0xFFFD] = LSB;
        cpu.memory[0xFFFE] = MSB;
        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_AB_Y_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_IN_X_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;
        cpu.X = testCase.X;

        Byte LSB = testCase.IndirectAddress & BIT_MASK_FIRST_BYTE;
        Byte MSB = testCase.IndirectAddress >> 8;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_IN_X_OPCODE;
        cpu.memory[0xFFFD] = testCase.Address;

        cpu.memory[testCase.ZeroPageAddress] = LSB;
        cpu.memory[testCase.ZeroPageAddress + 1] = MSB;

        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_IN_X_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }

    void ADC_IN_Y_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;
        cpu.Y = testCase.Y;

        Byte LSB = testCase.IndirectAddress & BIT_MASK_FIRST_BYTE;
        Byte MSB = testCase.IndirectAddress >> 8;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_IN_Y_OPCODE;
        cpu.memory[0xFFFD] = testCase.ZeroPageAddress;

        cpu.memory[testCase.ZeroPageAddress] = LSB;
        cpu.memory[testCase.ZeroPageAddress + 1] = MSB;

        cpu.memory[testCase.ExpectedAddress] = testCase.O;
        // End inline program

        int cycles = em6502_execute(&cpu, ADC_IN_Y_CYCLES);

        ASSERT_EQ(cycles, testCase.expectedCycles);

        ASSERT_EQ(cpu.A, testCase.ExpectedA);

        ASSERT_EQ(cpu.C, testCase.ExpectedC);
        ASSERT_EQ(cpu.Z, testCase.ExpectedZ);
        ASSERT_EQ(cpu.V, testCase.ExpectedV);
        ASSERT_EQ(cpu.N, testCase.ExpectedN);

        /* Make sure the rest are unaffected by the instruction */
        ASSERT_EQ(cpu.I, INTERRUPT_DISABLE_RESET_VALUE);
        ASSERT_EQ(cpu.D, DECIMAL_MODE_RESET_VALUE);
        ASSERT_EQ(cpu.B, BREAK_COMMAND_RESET_VALUE);
    }
};

#define ADC_IM_TEST 1

#define ADC_ZP_TEST 1
#define ADC_ZP_X_TEST 1

#define ADC_AB_TEST 1
#define ADC_AB_X_TEST 1
#define ADC_AB_Y_TEST 1

#define ADC_IN_X_TEST 1
#define ADC_IN_Y_TEST 1

#if ADC_IM_TEST

TEST_F(ADC_TEST, ADC_IM_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddTwoPositiveNumbersAndCarry)
{
    // C: 0000 0001
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1011

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 1;

    testCase.ExpectedA = 11;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddTwoNegativeNumbersAndCarry)
{
    // C:     0000 0001
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0111

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 1;

    testCase.ExpectedA = -9;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddNegativeAndPositiveNumber)
{
    // A:     1111 1011
    // O:     0000 1010
    // =: (1) 0000 0101

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = 10;
    testCase.C = 0;

    testCase.ExpectedA = 5;
    testCase.ExpectedC = true;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddNegativeAndPositiveNumberAndCarry)
{
    // C:     0000 0001
    // A:     1111 1011
    // O:     0000 1010
    // =: (1) 0000 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = 10;
    testCase.C = 1;

    testCase.ExpectedA = 6;
    testCase.ExpectedC = true;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_AddTwoPostiveNumberWithCarry)
{
    // A:     1111 1111
    // O:     0000 0001
    // =: (1) 0000 0000

    ADC_TestCase testCase;

    testCase.A = 255;
    testCase.O = 1;
    testCase.C = 0;

    testCase.ExpectedA = 0;
    testCase.ExpectedC = true;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = true;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_OverflowAddingTwoNegativeNumbers)
{
    // A:     1000 0000
    // O:     1111 1111
    // =: (1) 0111 1111

    ADC_TestCase testCase;

    testCase.A = -128;
    testCase.O = -1;
    testCase.C = 0;

    testCase.ExpectedA = 127;
    testCase.ExpectedC = true;
    testCase.ExpectedN = false;
    testCase.ExpectedV = true;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_OverflowAddingTwoPostiveNumbers)
{
    // A: 0111 1111
    // O: 0000 0001
    // =: 1000 0000

    ADC_TestCase testCase;

    testCase.A = 127;
    testCase.O = 1;
    testCase.C = 0;

    testCase.ExpectedA = 128;
    testCase.ExpectedC = false;
    testCase.ExpectedN = true;
    testCase.ExpectedV = true;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_OverflowAddingTwoPostiveNumbersAndCarry)
{
    // C: 0000 0001
    // A: 0111 1110
    // O: 0000 0001
    // =: 1000 0000

    ADC_TestCase testCase;

    testCase.A = 126;
    testCase.O = 1;
    testCase.C = 1;

    testCase.ExpectedA = 128;
    testCase.ExpectedC = false;
    testCase.ExpectedN = true;
    testCase.ExpectedV = true;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

TEST_F(ADC_TEST, ADC_IM_OverflowAddingTwoNegativeNumbersAndCarry)
{
    // C:     0000 0001
    // A:     1000 0000
    // O:     1111 1110
    // =: (1) 0111 1111

    ADC_TestCase testCase;

    testCase.A = -128;
    testCase.O = -2;
    testCase.C = 1;

    testCase.ExpectedA = 127;
    testCase.ExpectedC = true;
    testCase.ExpectedN = false;
    testCase.ExpectedV = true;
    testCase.ExpectedZ = false;

    testCase.expectedCycles = ADC_IM_CYCLES;

    ADC_IM_test(testCase);
}

#endif /* ADC_IM_TEST */

#if ADC_ZP_TEST

TEST_F(ADC_TEST, ADC_ZP_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Address = 0xF1;
    testCase.ExpectedAddress = 0xF1;

    testCase.expectedCycles = ADC_ZP_CYCLES;

    ADC_ZP_test(testCase);
}

TEST_F(ADC_TEST, ADC_ZP_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Address = 0x09;
    testCase.ExpectedAddress = 0x09;

    testCase.expectedCycles = ADC_ZP_CYCLES;

    ADC_ZP_test(testCase);
}

#endif /* ADC_ZP_TEST */

#if ADC_ZP_X_TEST

TEST_F(ADC_TEST, ADC_ZP_X_AddTwoPositiveNumbersWithWrap)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x80;
    testCase.Address = 0xFF;
    testCase.ExpectedAddress = 0x7F;

    testCase.expectedCycles = ADC_ZP_X_CYCLES;

    ADC_ZP_X_test(testCase);
}

TEST_F(ADC_TEST, ADC_ZP_X_AddTwoNegativeNumbersNoWrap)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x01;
    testCase.Address = 0x01;
    testCase.ExpectedAddress = 0x02;

    testCase.expectedCycles = ADC_ZP_X_CYCLES;

    ADC_ZP_X_test(testCase);
}

#endif /* ADC_ZP_X_TEST */

#if ADC_AB_TEST

TEST_F(ADC_TEST, ADC_AB_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Address = 0x8361;
    testCase.ExpectedAddress = 0x8361;

    testCase.expectedCycles = ADC_AB_CYCLES;

    ADC_AB_test(testCase);
}

TEST_F(ADC_TEST, ADC_AB_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Address = 0xFCD9;
    testCase.ExpectedAddress = 0xFCD9;

    testCase.expectedCycles = ADC_AB_CYCLES;

    ADC_AB_test(testCase);
}

#endif /* ADC_AB_TEST */

#if ADC_AB_X_TEST

TEST_F(ADC_TEST, ADC_AB_X_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x92;
    testCase.Address = 0x2000;
    testCase.ExpectedAddress = 0x2092;

    testCase.expectedCycles = ADC_AB_X_CYCLES;

    ADC_AB_X_test(testCase);
}

TEST_F(ADC_TEST, ADC_AB_X_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0xF9;
    testCase.Address = 0x2000;
    testCase.ExpectedAddress = 0x20F9;

    testCase.expectedCycles = ADC_AB_X_CYCLES;

    ADC_AB_X_test(testCase);
}

TEST_F(ADC_TEST, ADC_AB_X_AddTwoNegativeNumbersAndRunExtraCycle)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x001;
    testCase.Address = 0x00FF;
    testCase.ExpectedAddress = 0x0100;

    testCase.expectedCycles = ADC_AB_X_CYCLES + 1;

    ADC_AB_X_test(testCase);
}

#endif /* ADC_AB_X_TEST */

#if ADC_AB_Y_TEST

TEST_F(ADC_TEST, ADC_AB_Y_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0x92;
    testCase.Address = 0x2000;
    testCase.ExpectedAddress = 0x2092;

    testCase.expectedCycles = ADC_AB_Y_CYCLES;

    ADC_AB_Y_test(testCase);
}

TEST_F(ADC_TEST, ADC_AB_Y_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0xF9;
    testCase.Address = 0x2000;
    testCase.ExpectedAddress = 0x20F9;

    testCase.expectedCycles = ADC_AB_Y_CYCLES;

    ADC_AB_Y_test(testCase);
}

TEST_F(ADC_TEST, ADC_AB_Y_AddTwoNegativeNumbersAndRunExtraCycle)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0x001;
    testCase.Address = 0x00FF;
    testCase.ExpectedAddress = 0x0100;

    testCase.expectedCycles = ADC_AB_Y_CYCLES + 1;

    ADC_AB_Y_test(testCase);
}

#endif /* ADC_AB_Y_TEST */

#if ADC_IN_X_TEST

TEST_F(ADC_TEST, ADC_IN_X_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x04;
    testCase.Address = 0x20;
    testCase.ZeroPageAddress = 0x24;
    testCase.IndirectAddress = 0x2074;
    testCase.ExpectedAddress = 0x2074;

    testCase.expectedCycles = ADC_IN_X_CYCLES;

    ADC_IN_X_test(testCase);
}

TEST_F(ADC_TEST, ADC_IN_X_AddTwoNegativeNumbersWithWrap)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.X = 0x80;
    testCase.Address = 0xFF;
    testCase.ZeroPageAddress = 0x7F;

    testCase.IndirectAddress = 0x2000;
    testCase.ExpectedAddress = 0x2000;

    testCase.expectedCycles = ADC_IN_X_CYCLES;

    ADC_IN_X_test(testCase);
}

#endif /* ADC_IN_X_TEST */

#if ADC_IN_Y_TEST

TEST_F(ADC_TEST, ADC_IN_Y_AddTwoPositiveNumbers)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    ADC_TestCase testCase;

    testCase.A = 5;
    testCase.O = 5;
    testCase.C = 0;

    testCase.ExpectedA = 10;
    testCase.ExpectedC = false;
    testCase.ExpectedN = false;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0x10;
    testCase.ZeroPageAddress = 0x86;
    testCase.IndirectAddress = 0x4028;
    testCase.ExpectedAddress = 0x4038;

    testCase.expectedCycles = ADC_IN_Y_CYCLES;

    ADC_IN_Y_test(testCase);
}

TEST_F(ADC_TEST, ADC_IN_X_AddTwoNegativeNumbers)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0x20;
    testCase.ZeroPageAddress = 0x40;
    testCase.IndirectAddress = 0x4500;
    testCase.ExpectedAddress = 0x4520;

    testCase.expectedCycles = ADC_IN_Y_CYCLES;

    ADC_IN_Y_test(testCase);
}

TEST_F(ADC_TEST, ADC_IN_Y_AddTwoNegativeNumbersAndRunExtraCycle)
{
    // A:     1111 1011
    // O:     1111 1011
    // =: (1) 1111 0110

    ADC_TestCase testCase;

    testCase.A = -5;
    testCase.O = -5;
    testCase.C = 0;

    testCase.ExpectedA = -10;
    testCase.ExpectedC = true;
    testCase.ExpectedN = true;
    testCase.ExpectedV = false;
    testCase.ExpectedZ = false;

    testCase.Y = 0x001;
    testCase.ZeroPageAddress = 0x67;
    testCase.IndirectAddress = 0x00FF;
    testCase.ExpectedAddress = 0x0100;

    testCase.expectedCycles = ADC_IN_Y_CYCLES + 1;

    ADC_IN_Y_test(testCase);
}

#endif /* ADC_IN_Y_TEST */