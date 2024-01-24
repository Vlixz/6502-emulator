# 6502-emulator
Basic 6502 C emulator I am writing to get a better understanding of a basic CPU architecture.
- For now I'm not going the be implementing decimal mode but maybe when I'm finished I'll add it.
- I am writing all Unit Tests using gtest.

So far I've added the following instructions:
- ADC   (Add With Carry)
- AND   (Logical AND)
- ASL   (Arithmetic Shift Left)
- BCC   (Branch if Carry Clear)
- BCS   (Branch if Carry Set)
- BEQ   (Branch if Equal)
- BIT   (Bit Test)
- BMI   (Branch if Minus)
- BNE   (Branch if Not Equal)
- BPL   (Branch if Positive)
- BVC   (Branch if Overflow Clear)
- BVS   (Branch if Overflow Set)
- CLC   (Clear Carry Flag)
- CLD   (Clear Decimal Mode)
- CLI   (Clear Interrupt Disable)
- CLV   (Clear Overflow Flag)
- SEC   (Set Carry Flag)
- SED   (Set Decimal Mode) - Does not throw a error but not supported
- SEI   (Set Interrupt Disabled)
- TAX   (Transfer Accumulator to X)
- TAY   (Transfer Accumulator to Y)
- TXA   (Transfer X to Accumulator)
- TYA   (Transfer Y to Accumulator)
- LDA   (Load Accumulator)
- NOP   (No Operation)
- DEX   (Decrement the X register)
- DEY   (Decrement the Y register)
- LDX   (Load X Register)

Following have to be added:
- LDY   (Load Y Register)
- STA   (Store Accumulator)
- STX   (Store X Register)
- STY   (Store Y Register)

- TSX   (Transfer stack pointer to X)
- TXS   (Transfer X to stack pointer)
- PHA   (Push accumulator on stack)
- PHP   (Push processor status on stack)
- PLA   (Pull accumulator from stack)
- PLP   (Pull processor status from stack)

- EOR   (Exclusive OR)
- ORA   (Logical inclusive OR)

- SBC   (Subtract with Carry)
- CMP   (Compare accumulator)
- CPX   (Compare X register)
- CPY   (Compare Y register)

- INC   (Increment a memory location)
- INX   (Increment the X register)
- INY   (Increment the Y register)
- DEC   (Decrement a memory location)

- LSR   (Logical Shift Right)
- ROL   (Rotate left)
- ROR   (Rotate right)

- JMP   (Jump to another location)
- JSR   (Jump to a subroutine)
- RTS   (Return from subroutine)

- BRK   (Force an interrupt)
- RTI   (Return from interrupt)

So a long way to go xD (almost half way there)
