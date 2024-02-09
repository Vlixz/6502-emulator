# 6502 Emulator

I'm creating a simpel CLI tool to emulate the 6502 microprocessor. So far I've added all the instructions without the use of decimal mode
which I might add later on if I feel like it.

The program might still be a bit buggy but I'll polish it up (:

I used the [6502_65C02_functional_tests](https://github.com/Klaus2m5/6502_65C02_functional_tests) made by Klaus Dormann for testing.

## Features

- Easy way to look into the memory.
- Step by step execution, and continous execution.
- Way of defining the reset vector.

![image](https://github.com/Vlixz/6502-emulator/assets/71019504/8d171a13-4a2f-4b73-92c9-41fc70bc30f5)

## Building

To build the repository the only dependency you need is ncursus and cmake. 
I used Fedora Linux for building, but on Windows it should work fine too.

## Usage

To run the executable:
   
   ```
   ./em6502 <bin_file>
   ./em6502 <bin_file> -r <reset_vector>
   ```

For example:

   ```
   ./em6502 ../../bin_files/6502_functional_test.bin -r 0x0400
   ```
