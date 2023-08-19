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
    };

    void ADC_IM_test(AND_TestCase testCase)
    {
    }
};

TEST_F(AND_TEST, AND_TestExample)
{
    // A: 0000 0101
    // O: 0000 0101
    // =: 0000 1010

    AND_TestCase testCase;

    ADC_IM_test(testCase);
}
