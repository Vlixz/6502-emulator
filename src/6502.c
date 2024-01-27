#include "6502.h"

#include "stdlib.h"

void em6502_reset(CPU_6502 *cpu) {
    cpu->A = ACCUMULATOR_RESET_VALUE;
    cpu->B = BREAK_COMMAND_RESET_VALUE;
    cpu->C = CARRY_FLAG_RESET_VALUE;
    cpu->D = DECIMAL_MODE_RESET_VALUE;
    cpu->I = INTERRUPT_DISABLE_RESET_VALUE;
    cpu->N = NEGATIVE_FLAG_RESET_VALUE;
    cpu->V = OVERFLOW_FLAG_RESET_VALUE;
    cpu->Z = ZERO_FLAG_RESET_VALUE;

    cpu->PC = 0xFFFC;
    cpu->SP = START_OF_STACK;

    cpu->X = 0;
    cpu->Y = 0;

    cpu->memory = (Byte *)calloc(MEMORY_WORD_COUNT_6502, sizeof(Byte));
}

void em6502_destroy(CPU_6502 *cpu) { free(cpu->memory); }

int em6502_execute(CPU_6502 *cpu, int cycles) {
    int runCycles = 0, temp = 0;

    while (cycles > 0) {

        Word opcode = cpu->memory[cpu->PC++];

        switch (opcode) {

            /**
             * Add with Carry
             *
             */

        case ADC_IM_OPCODE:

            temp = ADC_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_ZP_OPCODE:

            temp = ADC_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_ZP_X_OPCODE:

            temp = ADC_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_OPCODE:

            temp = ADC_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_X_OPCODE:

            temp = ADC_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_AB_Y_OPCODE:

            temp = ADC_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_IN_X_OPCODE:

            temp = ADC_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ADC_IN_Y_OPCODE:

            temp = ADC_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Logical AND
             *
             */

        case AND_IM_OPCODE:

            temp = AND_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_ZP_OPCODE:

            temp = AND_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_ZP_X_OPCODE:

            temp = AND_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_OPCODE:

            temp = AND_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_X_OPCODE:

            temp = AND_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_AB_Y_OPCODE:

            temp = AND_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_IN_X_OPCODE:

            temp = AND_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case AND_IN_Y_OPCODE:

            temp = AND_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Arithmatic Shift Left
             *
             */

        case ASL_AC_OPCODE:

            temp = ASL_AC(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_ZP_OPCODE:

            temp = ASL_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_ZP_X_OPCODE:

            temp = ASL_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_AB_OPCODE:

            temp = ASL_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case ASL_AB_X_OPCODE:

            temp = ASL_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Carry Clear
             *
             */

        case BCC_RE_OPCODE:

            temp = BCC_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Carry Set
             *
             */

        case BCS_RE_OPCODE:

            temp = BCS_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Equal
             *
             */

        case BEQ_RE_OPCODE:

            temp = BEQ_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Bit Test
             *
             */

        case BIT_ZP_OPCODE:

            temp = BIT_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case BIT_AB_OPCODE:

            temp = BIT_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Minus
             *
             */

        case BMI_RE_OPCODE:

            temp = BMI_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Not Equal
             *
             */

        case BNE_RE_OPCODE:

            temp = BNE_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Positive
             *
             */

        case BPL_RE_OPCODE:

            temp = BPL_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Overflow Clear
             *
             */

        case BVC_RE_OPCODE:

            temp = BVC_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Branch if Overflow Set
             *
             */

        case BVS_RE_OPCODE:

            temp = BVS_RE(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Clear Carry Flag
             *
             */

        case CLC_IP_OPCODE:

            temp = CLC_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Clear Decimal Mode
             *
             */

        case CLD_IP_OPCODE:

            temp = CLD_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Clear Interrupt Disable
             *
             */

        case CLI_IP_OPCODE:

            temp = CLI_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Clear Overflow Flag
             *
             */

        case CLV_IP_OPCODE:

            temp = CLV_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Set Carry Flag
             *
             */

        case SEC_IP_OPCODE:

            temp = SEC_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Set Decimal Mode
             *
             */

        case SED_IP_OPCODE:

            temp = SED_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Set Interrupt Disable
             *
             */

        case SEI_IP_OPCODE:

            temp = SEI_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Transfer Accumulator to X
             *
             */

        case TAX_IP_OPCODE:

            temp = TAX_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Transfer Accumulator to Y
             *
             */

        case TAY_IP_OPCODE:

            temp = TAY_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Transfer X to Accumulator
             *
             */

        case TXA_IP_OPCODE:

            temp = TXA_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Transfer Y to Accumulator
             *
             */

        case TYA_IP_OPCODE:

            temp = TYA_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Load Accumulator
             *
             */

        case LDA_IM_OPCODE:

            temp = LDA_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_ZP_OPCODE:

            temp = LDA_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_ZP_X_OPCODE:

            temp = LDA_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_AB_OPCODE:

            temp = LDA_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_AB_X_OPCODE:

            temp = LDA_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_AB_Y_OPCODE:

            temp = LDA_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_IN_X_OPCODE:

            temp = LDA_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDA_IN_Y_OPCODE:

            temp = LDA_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * No Operation
             *
             */

        case NOP_IP_OPCODE:

            temp = NOP_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Decrement X
             *
             */

        case DEX_IP_OPCODE:

            temp = DEX_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Decrement Y
             *
             */

        case DEY_IP_OPCODE:

            temp = DEY_IP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Load X register
             *
             */

        case LDX_IM_OPCODE:
            temp = LDX_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDX_ZP_OPCODE:
            temp = LDX_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDX_ZP_Y_OPCODE:
            temp = LDX_ZP_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDX_AB_OPCODE:
            temp = LDX_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDX_AB_Y_OPCODE:
            temp = LDX_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Load Y register
             *
             */

        case LDY_IM_OPCODE:
            temp = LDY_IM(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDY_ZP_OPCODE:
            temp = LDY_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDY_ZP_X_OPCODE:
            temp = LDY_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDY_AB_OPCODE:
            temp = LDY_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case LDY_AB_X_OPCODE:
            temp = LDY_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

            /**
             * Load Y register
             *
             */

        case STA_ZP_OPCODE:
            temp = STA_ZP(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_ZP_X_OPCODE:
            temp = STA_ZP_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_AB_OPCODE:
            temp = STA_AB(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_AB_X_OPCODE:
            temp = STA_AB_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_AB_Y_OPCODE:
            temp = STA_AB_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_IN_X_OPCODE:
            temp = STA_IN_X(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        case STA_IN_Y_OPCODE:
            temp = STA_IN_Y(cpu);

            cycles -= temp;
            runCycles += temp;

            break;

        default:
            break;
        }
    }

    return runCycles;
}
