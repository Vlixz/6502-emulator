#ifndef INC_COMMON_H
#define INC_COMMON_H

#define Word unsigned long
#define Byte unsigned char

#define MEMORY_WORD_COUNT_6502 0xFFFF

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

#endif /* INC_COMMON_H*/