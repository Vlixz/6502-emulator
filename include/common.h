#ifndef INC_COMMON_H
#define INC_COMMON_H

#define Word unsigned long
#define Byte unsigned char

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

#endif /* INC_COMMON_H*/