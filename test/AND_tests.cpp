extern "C"
{
#include "6502.h"
}

#include <gtest/gtest.h>

class AND_TEST : public ::testing::Test
{
protected:
    CPU_6502 cpu;

    void SetUp() override
    {
        em6502_reset(&cpu);
    }

    ~AND_TEST() override
    {
        em6502_destroy(&cpu);
    }

    struct AND_TestCase
    {
        /* Input */
        Byte A; // Accumulator value
        Byte O; // Operator value

        /* Expected outcome */
        Byte ExpectedA; // Expected accumulator value
        bool ExpectedZ; // Expected Zero Flag
        bool ExpectedN; // Expected Negative Flag

        int expectedCycles;

        Word Address;
        Word ExpectedAddress;

        Byte ZeroPageAddress;
        Word IndirectAddress;

        Byte X;
        Byte Y;
    };

    void ADC_IM_test(AND_TestCase testCase)
    {
    }
};

TEST_F(AND_TEST, AND_TestExample)
{
    AND_TestCase testCase;

    ADC_IM_test(testCase);
}
