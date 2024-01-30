extern "C" {
#include "6502.h"
#include "instruction.h"
}

#include <gtest/gtest.h>

class ADDRESSINGMODE_TEST : public ::testing::Test {
  protected:
    void SetUp() override { em6502_reset(&cpu); }

    ~ADDRESSINGMODE_TEST() override { }

    struct TestCase {
        Word PC;
        Byte X;
        Byte Y;
        Word address;
        Byte zero_page_address;
        Byte zero_page_address_indirect;
        Word pointer;
        Word indirect_bug_address;
        Byte indirect_bug_value;
        Word expected_address;
        uint8_t cycles;
    };

    void IMM_test(TestCase testCase) {
        cpu.PC = testCase.PC;

        Word address;
        uint8_t cycles = IMM(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void ZP0_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address;

        Word address;
        uint8_t cycles = ZP0(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void ZPX_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address;
        cpu.X = testCase.X;
       
        Word address;
        uint8_t cycles = ZPX(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void ZPY_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address;
        cpu.Y = testCase.Y;
       
        Word address;
        uint8_t cycles = ZPY(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void AB0_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.PC + 1] = testCase.address >> 8; // MSB

        Word address;
        uint8_t cycles = AB0(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void ABX_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.PC + 1] = testCase.address >> 8; // MSB
        cpu.X = testCase.X;

        Word address;
        uint8_t cycles = ABX(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void ABY_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.PC + 1] = testCase.address >> 8; // MSB
        cpu.Y = testCase.Y;

        Word address;
        uint8_t cycles = ABY(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void IND_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.indirect_bug_address] = testCase.indirect_bug_value;
        cpu.memory[testCase.PC] = testCase.pointer & 0xFF;   // LSB
        cpu.memory[testCase.PC + 1] = testCase.pointer >> 8; // MSB

        cpu.memory[testCase.pointer] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.pointer + 1] = testCase.address >> 8; // MSB

        Word address;
        uint8_t cycles = IND(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void IIX_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.zero_page_address;
        cpu.X = testCase.X;
        cpu.memory[testCase.zero_page_address_indirect] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.zero_page_address_indirect + 1] = testCase.address >> 8; // MSB

        Word address;
        uint8_t cycles = IIX(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }

    void IIY_test(TestCase testCase) {
        cpu.PC = testCase.PC;
        cpu.memory[testCase.PC] = testCase.zero_page_address;
        cpu.memory[testCase.zero_page_address] = testCase.address & 0xFF;   // LSB
        cpu.memory[testCase.zero_page_address + 1] = testCase.address >> 8; // MSB
        cpu.Y = testCase.Y;

        Word address;
        uint8_t cycles = IIY(&address);

        EXPECT_EQ(address, testCase.expected_address);
        EXPECT_EQ(cycles, testCase.cycles);
    }
};

TEST_F(ADDRESSINGMODE_TEST, IMM_ReturnsPC) {
    TestCase testCase;

    testCase.PC = 0xFFFC;
    testCase.expected_address = 0xFFFC;
    testCase.cycles = 0;

    IMM_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ZP0_ReturnsValueAtAddress) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x42;
    testCase.expected_address = 0x42;
    testCase.cycles = 0;

    ZP0_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ZPX_ReturnsCorrectAddressNoWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x42;
    testCase.X = 0x01;
    testCase.expected_address = 0x43;
    testCase.cycles = 0;

    ZPX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ZPX_ReturnsCorrectAddressWithWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x80;
    testCase.X = 0xFF;
    testCase.expected_address = 0x7F;
    testCase.cycles = 0;

    ZPX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ZPY_ReturnsCorrectAddressNoWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x42;
    testCase.Y = 0x01;
    testCase.expected_address = 0x43;
    testCase.cycles = 0;

    ZPY_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ZPY_ReturnsCorrectAddressWithWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x80;
    testCase.Y = 0xFF;
    testCase.expected_address = 0x7F;
    testCase.cycles = 0;

    ZPY_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, AB0_ReturnsCorrectAddress) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x808F;
    testCase.expected_address = 0x808F;
    testCase.cycles = 0;

    AB0_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ABX_ReturnsCorrectAddressNoPageCrossed) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x8080;
    testCase.X = 0x02;
    testCase.expected_address = 0x8082;
    testCase.cycles = 0;

    ABX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ABX_ReturnsCorrectAddressPageCrossed) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x8080;
    testCase.X = 0xFF;
    testCase.expected_address = 0x817F;
    testCase.cycles = 1;

    ABX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ABY_ReturnsCorrectAddressNoPageCrossed) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x8084;
    testCase.Y = 0x02;
    testCase.expected_address = 0x8086;
    testCase.cycles = 0;

    ABY_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, ABY_ReturnsCorrectAddressPageCrossed) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.address = 0x8080;
    testCase.Y = 0xFF;
    testCase.expected_address = 0x817F;
    testCase.cycles = 1;

    ABY_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IND_ReturnsCorrectAddress) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.pointer = 0x8076;
    testCase.address = 0x80F0;
    testCase.expected_address = 0x80F0;
    testCase.cycles = 0;

    IND_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IND_ReturnsCorrectAddressPageBoundary) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.pointer = 0x80FF;
    testCase.address = 0x9080;
    testCase.indirect_bug_address = 0x8000;
    testCase.indirect_bug_value = 0x80;
    testCase.expected_address = 0x8080;
    testCase.cycles = 0;

    IND_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IIX_ReturnsCorrectAddressNoWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.zero_page_address = 0x80;
    testCase.X = 0x02;
    testCase.zero_page_address_indirect = 0x82;
    testCase.address = 0xFCF3;
    testCase.expected_address = 0xFCF3;
    testCase.cycles = 0;

    IIX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IIX_ReturnsCorrectAddressWrap) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.zero_page_address = 0xFF;
    testCase.X = 0x03;
    testCase.zero_page_address_indirect = 0x02;
    testCase.address = 0xFCF3;
    testCase.expected_address = 0xFCF3;
    testCase.cycles = 0;

    IIX_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IIY_ReturnsCorrectAddress) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.zero_page_address = 0x09;
    testCase.address = 0xFCF3;
    testCase.Y = 0x02;
    testCase.expected_address = 0xFCF5;
    testCase.cycles = 0;

    IIY_test(testCase);
}

TEST_F(ADDRESSINGMODE_TEST, IIY_ReturnsCorrectAddressPageBoundary) {
    TestCase testCase;

    testCase.PC = 0x0001;
    testCase.zero_page_address = 0x09;
    testCase.address = 0xFCFF;
    testCase.Y = 0x02;
    testCase.expected_address = 0xFD01;
    testCase.cycles = 1;

    IIY_test(testCase);
}