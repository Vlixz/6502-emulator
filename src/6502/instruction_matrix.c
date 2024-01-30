#include "instruction.h"

instruction instruction_matrix[16][16] = {

    {{"BRK", &BRK, &IMP, 7}, /* 0x0 */
     {"ORA", &ORA, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ZP0, 3},
     {"ASL", &ASL, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PHP", &PHP, &IMP, 3},
     {"ORA", &ORA, &IMM, 2},
     {"ASL", &ASL, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &AB0, 4},
     {"ASL", &ASL, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x0 */
                              /* 0x1 */
    {{"BPL", &BPL, &REL, 2},
     {"ORA", &ORA, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ZPX, 4},
     {"ASL", &ASL, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLC", &CLC, &IMP, 2},
     {"ORA", &ORA, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ORA", &ORA, &ABX, 4},
     {"ASL", &ASL, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x1 */
                              /* 0x2 */
    {{"JSR", &JSR, &AB0, 6},
     {"AND", &AND, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"BIT", &BIT, &ZP0, 3},
     {"AND", &AND, &ZP0, 3},
     {"ROL", &ROL, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PLP", &PLP, &IMP, 4},
     {"AND", &AND, &IMM, 2},
     {"ROL", &ROL, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"BIT", &BIT, &AB0, 4},
     {"AND", &AND, &AB0, 4},
     {"ROL", &ROL, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x2 */
                              /* 0x3 */
    {{"BMI", &BMI, &REL, 2},
     {"AND", &AND, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"AND", &AND, &ZPX, 4},
     {"ROL", &ROL, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SEC", &SEC, &IMP, 2},
     {"AND", &AND, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"AND", &AND, &ABX, 4},
     {"ROL", &ROL, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x3 */
                              /* 0x4 */
    {{"RTI", &RTI, &IMP, 6},
     {"EOR", &EOR, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ZP0, 3},
     {"LSR", &LSR, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PHA", &PHA, &IMP, 3},
     {"EOR", &EOR, &IMM, 2},
     {"LSR", &LSR, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"JMP", &JMP, &AB0, 3},
     {"EOR", &EOR, &AB0, 4},
     {"LSR", &LSR, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x4 */
                              /* 0x5 */
    {{"BVC", &BVC, &REL, 2},
     {"EOR", &EOR, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ZPX, 4},
     {"LSR", &LSR, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLI", &CLI, &IMP, 2},
     {"EOR", &EOR, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"EOR", &EOR, &ABX, 4},
     {"LSR", &LSR, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x5 */
                              /* 0x6 */
    {{"RTS", &RTS, &IMP, 6},
     {"ADC", &ADC, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ZP0, 3},
     {"ROR", &ROR, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"PLA", &PLA, &IMP, 4},
     {"ADC", &ADC, &IMM, 2},
     {"ROR", &ROR, &ACC, 2},
     {"???", &XXX, &IMP, 1},
     {"JMP", &JMP, &IND, 4},
     {"ADC", &ADC, &AB0, 4},
     {"ROR", &ROR, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0x6 */
                              /* 0x7 */
    {{"BVS", &BVS, &REL, 2},
     {"ADC", &ADC, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ZPX, 4},
     {"ROR", &ROR, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SEI", &SEI, &IMP, 2},
     {"ADC", &ADC, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"ADC", &ADC, &ABX, 4},
     {"ROR", &ROR, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0x7 */
                              /* 0x8 */
    {{"???", &XXX, &IMP, 0},
     {"STA", &STA, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &ZP0, 3},
     {"STA", &STA, &ZP0, 3},
     {"STX", &STX, &ZP0, 3},
     {"???", &XXX, &IMP, 1},
     {"DEY", &DEY, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"TXA", &TXA, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &AB0, 4},
     {"STA", &STA, &AB0, 4},
     {"STX", &STX, &AB0, 4},
     {"???", &XXX, &IMP, 1}}, /* 0x8 */
                              /* 0x9 */
    {{"BCC", &BCC, &REL, 2},
     {"STA", &STA, &IIY, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STY", &STY, &ZPX, 4},
     {"STA", &STA, &ZPX, 4},
     {"STX", &STX, &ZPY, 4},
     {"???", &XXX, &IMP, 1},
     {"TYA", &TYA, &IMP, 2},
     {"STA", &STA, &ABY, 5},
     {"TXS", &TXS, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"STA", &STA, &ABX, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1}}, /* 0x9 */
                              /* 0xA */
    {{"LDY", &LDY, &IMM, 2},
     {"LDA", &LDA, &IIX, 6},
     {"LDX", &LDX, &IMM, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ZP0, 3},
     {"LDA", &LDA, &ZP0, 3},
     {"LDX", &LDX, &ZP0, 3},
     {"???", &XXX, &IMP, 1},
     {"TAY", &TAY, &IMP, 2},
     {"LDA", &LDA, &IMM, 2},
     {"TAX", &TAX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &AB0, 4},
     {"LDA", &LDA, &AB0, 4},
     {"LDX", &LDX, &AB0, 4},
     {"???", &XXX, &IMP, 1}}, /* 0xA */
                              /* 0xB */
    {{"BCS", &BCS, &REL, 2},
     {"LDA", &LDA, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ZPX, 4},
     {"LDA", &LDA, &ZPX, 4},
     {"LDX", &LDX, &ZPY, 4},
     {"???", &XXX, &IMP, 1},
     {"CLV", &CLV, &IMP, 2},
     {"LDA", &LDA, &ABY, 4},
     {"TSX", &TSX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"LDY", &LDY, &ABX, 4},
     {"LDA", &LDA, &ABX, 4},
     {"LDX", &LDX, &ABY, 4},
     {"???", &XXX, &IMP, 1}}, /* 0xB */
                              /* 0xC */
    {{"CPY", &CPY, &IMM, 2},
     {"CMP", &CMP, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CPY", &CPY, &ZP0, 3},
     {"CMP", &CMP, &ZP0, 3},
     {"DEC", &DEC, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"INY", &INY, &IMP, 2},
     {"CMP", &CMP, &IMM, 2},
     {"DEX", &DEX, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"CPY", &CPY, &AB0, 4},
     {"CMP", &CMP, &AB0, 4},
     {"DEC", &DEC, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0xC */
                              /* 0xD */
    {{"BNE", &BNE, &REL, 2},
     {"CMP", &CMP, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CMP", &CMP, &ZPX, 4},
     {"DEC", &DEC, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"CLD", &CLD, &IMP, 2},
     {"CMP", &CMP, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CMP", &CMP, &ABX, 4},
     {"DEC", &DEC, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0xD */
                              /* 0xE */
    {{"CPX", &CPX, &IMM, 2},
     {"SBC", &SBC, &IIX, 6},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"CPX", &CPX, &ZP0, 3},
     {"SBC", &SBC, &ZP0, 3},
     {"INC", &INC, &ZP0, 5},
     {"???", &XXX, &IMP, 1},
     {"INX", &INX, &IMP, 2},
     {"SBC", &SBC, &IMM, 2},
     {"NOP", &NOP, &IMP, 2},
     {"???", &XXX, &IMP, 1},
     {"CPX", &CPX, &AB0, 4},
     {"SBC", &SBC, &AB0, 4},
     {"INC", &INC, &AB0, 6},
     {"???", &XXX, &IMP, 1}}, /* 0xE */
                              /* 0xF */
    {{"BEQ", &BEQ, &REL, 2},
     {"SBC", &SBC, &IIY, 5},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"SBC", &SBC, &ZPX, 4},
     {"INC", &INC, &ZPX, 6},
     {"???", &XXX, &IMP, 1},
     {"SED", &SED, &IMP, 2},
     {"SBC", &SBC, &ABY, 4},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"???", &XXX, &IMP, 1},
     {"SBC", &SBC, &ABX, 4},
     {"INC", &INC, &ABX, 7},
     {"???", &XXX, &IMP, 1}}, /* 0xF */
};