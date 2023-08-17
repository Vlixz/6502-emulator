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
        reset_6502(&cpu);
    }

    ~ADC_TEST() override
    {
        destroy_6502(&cpu);
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
    };

    void ADC_IM_test(ADC_TestCase testCase)
    {
        cpu.A = testCase.A;
        cpu.C = testCase.C;

        // Start inline program
        cpu.memory[0xFFFC] = ADC_IM_OPCODE;
        cpu.memory[0xFFFD] = testCase.O;
        // End inline program

        execute_6502(&cpu, ADC_IM_CYCLES);

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

    ADC_IM_test(testCase);
}