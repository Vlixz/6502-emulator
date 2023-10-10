# 6502-emulator

Basic 6502 C emulator I am writing to get a better understanding of a basic CPU architecture.
- For now I'm not going the be implementing decimal mode but maybe when I'm finished I'll add it.

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

I am writing all Unit Tests using gtest
