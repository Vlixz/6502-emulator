#include "6502.h"

// =======================================
//                  CPU
// =======================================

CPU_6502 cpu;

void reset( void ) {
    
    cpu.PC = 0;
    cpu.SP = START_OF_STACK;

    cpu.AC = 0;
    cpu.BC = 0;
    cpu.CF = 0; 
    cpu.DM = 0;
    cpu.ID = 0;
    cpu.NF = 0;
    cpu.OF = 0;
    
    cpu.ZF = 0;
    cpu.X = 0;
    cpu.Y = 0;
}

void execute( int cycles ) {
    
}

// =======================================
//             Add with Carry
// =======================================

void ADC_IM( void ) {

}

void ADC_ZP( void ) {

}

void ADC_ZP_X( void ) {

}

void ADC_AB( void ) {

}

void ADC_AB_X( void ) {

}

void ADC_AB_Y( void ) {

}

void ADC_IN_X( void ) {

}

void ADC_IN_Y( void ) {

}
