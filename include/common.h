#ifndef INC_COMMON_H
#define INC_COMMON_H

#define Word unsigned short
#define Byte unsigned char

#define IS_NEGATIVE(x) (((x) & BIT_MASK_SIGNED) > 0)

#define MEMORY_WORD_COUNT_6502 0xFFFF

// =======================================
//               BitMasks
// =======================================
#define BIT_MASK_SIGNED 0b10000000
#define BIT_MASK_CARRY 0b100000000
#define BIT_MASK_FIRST_BYTE 0x00FF
#define BIT_MASK_LAST_BYTE 0xFF00

// =======================================
//              Reset values
// =======================================

#define ACCUMULATOR_RESET_VALUE 0
#define BREAK_COMMAND_RESET_VALUE 0
#define CARRY_FLAG_RESET_VALUE 0
#define DECIMAL_MODE_RESET_VALUE 0
#define INTERRUPT_DISABLE_RESET_VALUE 0
#define NEGATIVE_FLAG_RESET_VALUE 0
#define OVERFLOW_FLAG_RESET_VALUE 0
#define ZERO_FLAG_RESET_VALUE 0

/**
 * Naming scheme Addressing Modes:
 *  IP      = Implied
 *  IM      = Immediate
 *  ZP      = Zero Page
 *  ZP_X    = Zero Page X
 *  ZP_Y    = Zero Page Y
 *  AB      = Absolute
 *  AB_X    = Absolute X
 *  AB_Y    = Absolute Y
 *  IN      = Indirect
 *  IN_X    = Indirect X (Indexed indirect)
 *  IN_Y    = Indirect Y (Indirect indexed)
 */

// =======================================
//             Add with Carry
// =======================================

#define ADC_IM_OPCODE 0x69
#define ADC_ZP_OPCODE 0x65
#define ADC_ZP_X_OPCODE 0x75
#define ADC_AB_OPCODE 0x6D
#define ADC_AB_X_OPCODE 0x7D
#define ADC_AB_Y_OPCODE 0x79
#define ADC_IN_X_OPCODE 0x61
#define ADC_IN_Y_OPCODE 0x71

#define ADC_IM_CYCLES 2
#define ADC_ZP_CYCLES 3
#define ADC_ZP_X_CYCLES 4
#define ADC_AB_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define ADC_AB_X_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define ADC_AB_Y_CYCLES 4
#define ADC_IN_X_CYCLES 6
/* Extra cycles is added when a page is crossed */
#define ADC_IN_Y_CYCLES 5

// =======================================
//             Logical AND
// =======================================

#define AND_IM_OPCODE 0x29
#define AND_ZP_OPCODE 0x25
#define AND_ZP_X_OPCODE 0x35
#define AND_AB_OPCODE 0x2D
#define AND_AB_X_OPCODE 0x3D
#define AND_AB_Y_OPCODE 0x39
#define AND_IN_X_OPCODE 0x21
#define AND_IN_Y_OPCODE 0x31

#define AND_IM_CYCLES 2
#define AND_ZP_CYCLES 3
#define AND_ZP_X_CYCLES 4
#define AND_AB_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define AND_AB_X_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define AND_AB_Y_CYCLES 4
#define AND_IN_X_CYCLES 6
#define AND_AB_X_CYCLES 4
#define AND_IN_X_CYCLES 6
/* Extra cycles is added when a page is crossed */
#define AND_IN_Y_CYCLES 5

// =======================================
//        Arithmatic Shift Left
// =======================================

#define ASL_AC_OPCODE 0x0A
#define ASL_ZP_OPCODE 0x06
#define ASL_ZP_X_OPCODE 0x16
#define ASL_AB_OPCODE 0x0E
#define ASL_AB_X_OPCODE 0x1E

#define ASL_AC_CYCLES 2
#define ASL_ZP_CYCLES 5
#define ASL_ZP_X_CYCLES 6
#define ASL_AB_CYCLES 6
#define ASL_AB_X_CYCLES 7

// =======================================
//         Branch if Carry Clear
// =======================================

#define BCC_RE_OPCODE 0x90

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BCC_RE_CYCLES 2

// =======================================
//          Branch if Carry Set
// =======================================

#define BCS_RE_OPCODE 0xB0

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BCS_RE_CYCLES 2

// =======================================
//           Branch if Equal
// =======================================

#define BEQ_RE_OPCODE 0xF0

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BEQ_RE_CYCLES 2

// =======================================
//              Bit Tests
// =======================================

#define BIT_ZP_OPCODE 0x24
#define BIT_AB_OPCODE 0x2C

#define BIT_ZP_CYCLES 3
#define BIT_AB_CYCLES 4

// =======================================
//            Branch if Minus
// =======================================

#define BMI_RE_OPCODE 0x30

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BMI_RE_CYCLES 2

// =======================================
//            Branch if Not Equal
// =======================================

#define BNE_RE_OPCODE 0xD0

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BNE_RE_CYCLES 2

// =======================================
//            Branch if Positive
// =======================================

#define BPL_RE_OPCODE 0x10

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BPL_RE_CYCLES 2

// =======================================
//       Branch if Overflow Clear
// =======================================

#define BVC_RE_OPCODE 0x50

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BVC_RE_CYCLES 2

// =======================================
//       Branch if Overflow Set
// =======================================

#define BVS_RE_OPCODE 0x70

/* Extra cycles if branch succeeds and +2 if to a new page */
#define BVS_RE_CYCLES 2

// =======================================
//            Clear Carry Flag
// =======================================

#define CLC_IP_OPCODE 0x18

#define CLC_IP_CYCLES 2

// =======================================
//          Clear Decimal Mode
// =======================================

#define CLD_IP_OPCODE 0xD8

#define CLD_IP_CYCLES 2

// =======================================
//        Clear Interrupt Disable
// =======================================

#define CLI_IP_OPCODE 0x58

#define CLI_IP_CYCLES 2

// =======================================
//          Clear Overflow Flag
// =======================================

#define CLV_IP_OPCODE 0xB8

#define CLV_IP_CYCLES 2

// =======================================
//            Set Carry Flag
// =======================================

#define SEC_IP_OPCODE 0x38

#define SEC_IP_CYCLES 2

// =======================================
//           Set Decimal Mode
// =======================================

#define SED_IP_OPCODE 0xF8

#define SED_IP_CYCLES 2

// =======================================
//           Set Interrupt Disable
// =======================================

#define SEI_IP_OPCODE 0x78

#define SEI_IP_CYCLES 2

// =======================================
//       Transfer Accumulator to X
// =======================================

#define TAX_IP_OPCODE 0xAA

#define TAX_IP_CYCLES 2

// =======================================
//       Transfer Accumulator to Y
// =======================================

#define TAY_IP_OPCODE 0xA8

#define TAY_IP_CYCLES 2

// =======================================
//       Transfer X to Accumulator
// =======================================

#define TXA_IP_OPCODE 0x8A

#define TXA_IP_CYCLES 2

// =======================================
//       Transfer Y to Accumulator
// =======================================

#define TYA_IP_OPCODE 0x98

#define TYA_IP_CYCLES 2

// =======================================
//            Load Accumulator
// =======================================

#define LDA_IM_OPCODE 0xA9
#define LDA_ZP_OPCODE 0xA5
#define LDA_ZP_X_OPCODE 0xB5
#define LDA_AB_OPCODE 0xAD
#define LDA_AB_X_OPCODE 0xBD
#define LDA_AB_Y_OPCODE 0xB9
#define LDA_IN_X_OPCODE 0xA1
#define LDA_IN_Y_OPCODE 0xB1

#define LDA_IM_CYCLES 2
#define LDA_ZP_CYCLES 3
#define LDA_ZP_X_CYCLES 4
#define LDA_AB_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define LDA_AB_X_CYCLES 4
/* Extra cycles is added when a page is crossed */
#define LDA_AB_Y_CYCLES 4
#define LDA_IN_X_CYCLES 6
/* Extra cycles is added when a page is crossed */
#define LDA_IN_Y_CYCLES 5

#endif /* INC_COMMON_H*/