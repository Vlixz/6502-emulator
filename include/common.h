#ifndef INC_COMMON_H
#define INC_COMMON_H

#define Word unsigned short
#define Byte unsigned char

/**
 * Macros
 *
 */
#define IS_NEGATIVE(x) (((x) & BIT_MASK_SIGNED) > 0)
#define IS_ZERO(x) ((x) == 0)
#define DID_CROSS_PAGE_BOUNDARY(LSB, X) ((Byte)(LSB + X) < X)
#define COMBINE_BYTES_LITTLE_ENDIAN(HIGH, LOW) ((HIGH << 8) | LOW)

/**
 * Handy constants
 * 
 */
#define NO_EXTRA_CYCLES 0

/*
 * Bitmasks
 */
#define BIT_MASK_SIGNED 0b10000000
#define BIT_MASK_CARRY 0b100000000
#define BIT_MASK_FIRST_BYTE 0x00FF
#define BIT_MASK_LAST_BYTE 0xFF00

/*
 * Naming scheme Addressing Modes:
 *    ACC    = Accumulator
 *    IMP    = Implied
 *    IMM    = Immediate
 *    ZP0    = Zero Page
 *    ZPX    = Zero Page X
 *    ZPY    = Zero Page Y
 *    AB0    = Absolute
 *    ABX    = Absolute X
 *    ABY    = Absolute Y
 *    IND    = Indirect
 *    INX    = Indirect X (Indexed indirect)
 *    INY    = Indirect Y (Indirect indexed)
 */

#define ADC_IMM_OPCODE 0x69
#define ADC_ZP0_OPCODE 0x65
#define ADC_ZPX_OPCODE 0x75
#define ADC_AB0_OPCODE 0x6D
#define ADC_ABX_OPCODE 0x7D
#define ADC_ABY_OPCODE 0x79
#define ADC_INX_OPCODE 0x61
#define ADC_INY_OPCODE 0x71

#define ADC_IMM_CYCLES 2
#define ADC_ZP0_CYCLES 3
#define ADC_ZPX_CYCLES 4
#define ADC_AB0_CYCLES 4
#define ADC_ABX_CYCLES 4
#define ADC_ABY_CYCLES 4
#define ADC_INX_CYCLES 6
#define ADC_INY_CYCLES 5

#define AND_IMM_OPCODE 0x29
#define AND_ZP0_OPCODE 0x25
#define AND_ZPX_OPCODE 0x35
#define AND_AB0_OPCODE 0x2D
#define AND_ABX_OPCODE 0x3D
#define AND_ABY_OPCODE 0x39
#define AND_INX_OPCODE 0x21
#define AND_INY_OPCODE 0x31

#define AND_IMM_CYCLES 2
#define AND_ZP0_CYCLES 3
#define AND_ZPX_CYCLES 4
#define AND_AB0_CYCLES 4
#define AND_ABX_CYCLES 4
#define AND_ABY_CYCLES 4
#define AND_INX_CYCLES 6
#define AND_ABX_CYCLES 4
#define AND_INX_CYCLES 6
#define AND_INY_CYCLES 5

#define ASL_ACC_OPCODE 0x0A
#define ASL_ZP0_OPCODE 0x06
#define ASL_ZPX_OPCODE 0x16
#define ASL_AB0_OPCODE 0x0E
#define ASL_ABX_OPCODE 0x1E

#define ASL_ACC_CYCLES 2
#define ASL_ZP0_CYCLES 5
#define ASL_ZPX_CYCLES 6
#define ASL_AB0_CYCLES 6
#define ASL_ABX_CYCLES 7

#define BCC_REL_OPCODE 0x90

#define BCC_REL_CYCLES 2

#define BCS_REL_OPCODE 0xB0

#define BCS_REL_CYCLES 2

#define BEQ_REL_OPCODE 0xF0

#define BEQ_REL_CYCLES 2

#define BIT_ZP0_OPCODE 0x24
#define BIT_AB0_OPCODE 0x2C

#define BIT_ZP0_CYCLES 3
#define BIT_AB0_CYCLES 4

#define BMI_REL_OPCODE 0x30

#define BMI_REL_CYCLES 2

#define BNE_REL_OPCODE 0xD0

#define BNE_REL_CYCLES 2

#define BPL_REL_OPCODE 0x10

#define BPL_REL_CYCLES 2

#define BRK_IMP_OPCODE 0x00

#define BRK_IMP_CYCLES 7

#define BVC_REL_OPCODE 0x50

#define BVC_REL_CYCLES 2

#define BVS_REL_OPCODE 0x70

#define BVS_REL_CYCLES 2

#define CLC_IMP_OPCODE 0x18

#define CLC_IMP_CYCLES 2

#define CLD_IMP_OPCODE 0xD8

#define CLD_IMP_CYCLES 2

#define CLI_IMP_OPCODE 0x58

#define CLI_IMP_CYCLES 2

#define CLV_IMP_OPCODE 0xB8

#define CLV_IMP_CYCLES 2

#define CMP_IMM_OPCODE 0xC9
#define CMP_ZP0_OPCODE 0xC5
#define CMP_ZPX_OPCODE 0xD5
#define CMP_AB0_OPCODE 0xCD
#define CMP_ABX_OPCODE 0xDD
#define CMP_ABY_OPCODE 0xD9
#define CMP_INX_OPCODE 0xC1
#define CMP_INY_OPCODE 0xD1

#define CMP_IMM_CYCLES 2
#define CMP_ZP0_CYCLES 3
#define CMP_ZPX_CYCLES 4
#define CMP_AB0_CYCLES 4
#define CMP_ABX_CYCLES 4
#define CMP_ABY_CYCLES 4
#define CMP_INX_CYCLES 6
#define CMP_INY_CYCLES 5

#define CPX_IMM_OPCODE 0xE0
#define CPX_ZP0_OPCODE 0xE4
#define CPX_AB0_OPCODE 0xEC

#define CPX_IMM_CYCLES 2
#define CPX_ZP0_CYCLES 3
#define CPX_AB0_CYCLES 4

#define CPY_IMM_OPCODE 0xC0
#define CPY_ZP0_OPCODE 0xC4
#define CPY_AB0_OPCODE 0xCC

#define CPY_IMM_CYCLES 2
#define CPY_ZP0_CYCLES 3
#define CPY_AB0_CYCLES 4

#define DEC_ZP0_OPCODE 0xC6
#define DEC_ZPX_OPCODE 0xD6
#define DEC_AB0_OPCODE 0xCE
#define DEC_ABX_OPCODE 0xDE

#define DEC_ZP0_CYCLES 5
#define DEC_ZPX_CYCLES 6
#define DEC_AB0_CYCLES 6
#define DEC_ABX_CYCLES 7

#define DEX_IMP_OPCODE 0xCA

#define DEX_IMP_CYCLES 2

#define DEY_IMP_OPCODE 0x88

#define DEY_IMP_CYCLES 2

#define EOR_IMM_OPCODE 0x49
#define EOR_ZP0_OPCODE 0x45
#define EOR_ZPX_OPCODE 0x55
#define EOR_AB0_OPCODE 0x4D
#define EOR_ABX_OPCODE 0x5D
#define EOR_ABY_OPCODE 0x59
#define EOR_INX_OPCODE 0x41
#define EOR_INY_OPCODE 0x51

#define EOR_IMM_CYCLES 2
#define EOR_ZP0_CYCLES 3
#define EOR_ZPX_CYCLES 4
#define EOR_AB0_CYCLES 4
#define EOR_ABX_CYCLES 4
#define EOR_ABY_CYCLES 4
#define EOR_INX_CYCLES 6
#define EOR_INY_CYCLES 5

#define INC_ZP0_OPCODE 0xE6
#define INC_ZPX_OPCODE 0xF6
#define INC_AB0_OPCODE 0xEE
#define INC_ABX_OPCODE 0xFE

#define INC_ZP0_CYCLES 5
#define INC_ZPX_CYCLES 6
#define INC_AB0_CYCLES 6
#define INC_ABX_CYCLES 7

#define INX_IMP_OPCODE 0xE8

#define INX_IMP_CYCLES 2

#define INY_IMP_OPCODE 0xC8

#define INY_IMP_CYCLES 2

#define JMP_AB0_OPCODE 0x4C
#define JMP_IND_OPCODE 0x6C

#define JMP_AB0_CYCLES 3
#define JMP_IND_CYCLES 5

#define JSR_AB0_OPCODE 20

#define JSR_AB0_CYCLES 6

#define LDA_IMM_OPCODE 0xA9
#define LDA_ZP0_OPCODE 0xA5
#define LDA_ZPX_OPCODE 0xB5
#define LDA_AB0_OPCODE 0xAD
#define LDA_ABX_OPCODE 0xBD
#define LDA_ABY_OPCODE 0xB9
#define LDA_INX_OPCODE 0xA1
#define LDA_INY_OPCODE 0xB1

#define LDA_IMM_CYCLES 2
#define LDA_ZP0_CYCLES 3
#define LDA_ZPX_CYCLES 4
#define LDA_AB0_CYCLES 4
#define LDA_ABX_CYCLES 4
#define LDA_ABY_CYCLES 4
#define LDA_INX_CYCLES 6
#define LDA_INY_CYCLES 5

#define LDX_IMM_OPCODE 0xA2
#define LDX_ZP0_OPCODE 0xA6
#define LDX_ZPY_OPCODE 0xB6
#define LDX_AB0_OPCODE 0xAE
#define LDX_ABY_OPCODE 0xBE

#define LDX_IMM_CYCLES 2
#define LDX_ZP0_CYCLES 3
#define LDX_ZPY_CYCLES 4
#define LDX_AB0_CYCLES 4
#define LDX_ABY_CYCLES 4

#define LDY_IMM_OPCODE 0xA0
#define LDY_ZP0_OPCODE 0xA4
#define LDY_ZPX_OPCODE 0xB4
#define LDY_AB0_OPCODE 0xAC
#define LDY_ABX_OPCODE 0xBC

#define LDY_IMM_CYCLES 2
#define LDY_ZP0_CYCLES 3
#define LDY_ZPX_CYCLES 4
#define LDY_AB0_CYCLES 4
#define LDY_ABX_CYCLES 4

#define LSR_ACC_OPCODE 0x4A
#define LSR_ZP0_OPCODE 0x46
#define LSR_ZPX_OPCODE 0x56
#define LSR_AB0_OPCODE 0x4E
#define LSR_ABX_OPCODE 0x5E

#define LSR_ACC_CYCLES 2
#define LSR_ZP0_CYCLES 5
#define LSR_ZPX_CYCLES 6
#define LSR_AB0_CYCLES 6
#define LSR_ABX_CYCLES 7

#define NOP_IMP_OPCODE 0xEA

#define NOP_IMP_CYCLES 2

#define ORA_IMM_OPCODE 0x09
#define ORA_ZP0_OPCODE 0x05
#define ORA_ZPX_OPCODE 0x15
#define ORA_AB0_OPCODE 0x0D
#define ORA_ABX_OPCODE 0x1D
#define ORA_ABY_OPCODE 0x19
#define ORA_INX_OPCODE 0x01
#define ORA_INY_OPCODE 0x11

#define ORA_IMM_CYCLES 2
#define ORA_ZP0_CYCLES 3
#define ORA_ZPX_CYCLES 4
#define ORA_AB0_CYCLES 4
#define ORA_ABX_CYCLES 4
#define ORA_ABY_CYCLES 4
#define ORA_INX_CYCLES 6
#define ORA_INY_CYCLES 5

#define PHA_IMP_OPCODE 0x48

#define PHA_IMP_CYCLES 3

#define PHP_IMP_OPCODE 0x08

#define PHP_IMP_CYCLES 3

#define PLP_IMP_OPCODE 0x68

#define PLP_IMP_CYCLES 4

#define ROL_ACC_OPCODE 0x2A
#define ROL_ZP0_OPCODE 0x26
#define ROL_ZPX_OPCODE 0x36
#define ROL_AB0_OPCODE 0x2E
#define ROL_ABX_OPCODE 0x3E

#define ROL_ACC_CYCLES 2
#define ROL_ZP0_CYCLES 5
#define ROL_ZPX_CYCLES 6
#define ROL_AB0_CYCLES 6
#define ROL_ABX_CYCLES 7

#define ROR_ACC_OPCODE 0x6A
#define ROR_ZP0_OPCODE 0x66
#define ROR_ZPX_OPCODE 0x76
#define ROR_AB0_OPCODE 0x6E
#define ROR_ABX_OPCODE 0x7E

#define ROR_ACC_CYCLES 2
#define ROR_ZP0_CYCLES 5
#define ROR_ZPX_CYCLES 6
#define ROR_AB0_CYCLES 6
#define ROR_ABX_CYCLES 7

#define RTI_IMP_OPCODE 0x40

#define RTA_IMP_CYCLES 6

#define RTS_IMP_OPCODE 0x60

#define RTS_IMP_CYCLES 6

#define SBC_IMM_OPCODE 0xE9
#define SBC_ZP0_OPCODE 0xE5
#define SBC_ZPX_OPCODE 0xF5
#define SBC_AB0_OPCODE 0xED
#define SBC_ABX_OPCODE 0xFD
#define SBC_ABY_OPCODE 0xF9
#define SBC_INX_OPCODE 0xE1
#define SBC_INY_OPCODE 0xF1

#define SBC_IMM_CYCLES 2
#define SBC_ZP0_CYCLES 3
#define SBC_ZPX_CYCLES 4
#define SBC_AB0_CYCLES 4
#define SBC_ABX_CYCLES 4
#define SBC_ABY_CYCLES 4
#define SBC_INX_CYCLES 6
#define SBC_INY_CYCLES 5

#define SEC_IMP_OPCODE 0x38

#define SEC_IMP_CYCLES 2

#define SED_IMP_OPCODE 0xF8

#define SED_IMP_CYCLES 2

#define SEI_IMP_OPCODE 0x78

#define SEI_IMP_CYCLES 2

#define STA_ZP0_OPCODE 0x85
#define STA_ZPX_OPCODE 0x95
#define STA_AB0_OPCODE 0x8D
#define STA_ABX_OPCODE 0x9D
#define STA_ABY_OPCODE 0x99
#define STA_INX_OPCODE 0x81
#define STA_INY_OPCODE 0x91

#define STA_ZP0_CYCLES 3
#define STA_ZPX_CYCLES 4
#define STA_AB0_CYCLES 4
#define STA_ABX_CYCLES 5
#define STA_ABY_CYCLES 5
#define STA_INX_CYCLES 6
#define STA_INY_CYCLES 6

#define STX_ZP0_OPCODE 0x86
#define STX_ZPY_OPCODE 0x96
#define STX_AB0_OPCODE 0x8E

#define STX_ZP0_CYCLES 3
#define STX_ZPY_CYCLES 4
#define STX_AB0_CYCLES 4

#define STY_ZP0_OPCODE 0x84
#define STY_ZPX_OPCODE 0x94
#define STY_AB0_OPCODE 0x8C

#define STY_ZP0_CYCLES 3
#define STY_ZPX_CYCLES 4
#define STY_AB0_CYCLES 4

#define TAX_IMP_OPCODE 0xAA

#define TAX_IMP_CYCLES 2

#define TAY_IMP_OPCODE 0xA8

#define TAY_IMP_CYCLES 2

#define TSX_IMP_OPCODE 0xBA

#define TSX_IMP_CYCLES 2

#define TXA_IMP_OPCODE 0x8A

#define TXA_IMP_CYCLES 2

#define TXS_IMP_OPCODE 0x9A

#define TXS_IMP_CYCLES 2

#define TYA_IMP_OPCODE 0x98

#define TYA_IMP_CYCLES 2

#endif /* INC_COMMON_H*/
