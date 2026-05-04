## Qzen-Emulator

a 8-bit cpu architecture which i made up , it has 2 examples inside that visualizes registers, mmio addresses etc..

examples are : 

**Examples/GPUVisualizer** --> If you have raylib installed on your compiler , you can build it

**Examples/CLIVisualizer** --> Portable cli version of visualizer

-------------------------------------------------------------------------------------------

### Build

building GPU accelerated visualizer 

    cmake -B build/
    cmake --build build/ --target GPUVisualizer

building CLI visualizer

    cmake -B build/
    cmake --build build/ --target CLIVisualizer
  
---------------------------------------------------------------------------------------------
### Registers

Register | Size | Info | Code
--- | --- | --- | ---
A | 8 bit | General Purpose | 0x00
B | 8 bit | General Purpose | 0x01
C | 8 bit | General Purpose | 0x02
D | 8 bit | General Purpose | 0x03
PC | 8 bit | Program counter | 0x04
FLAGS | 8 bit | overflow, sign , zero bits | 0x05

**Memory Size :** 64 kilo bytes



### Instruction Set
---------------------------------------------------------------------------------------------

Instruction | Purpose | Machine Code Macro
--- | --- | ---
0x00 | load memory to A register | _LB_A 
0x01 | load memory to B register | _LB_B
0x02 | load memory to C register | _LB_C
0x03 | load memory to D register | _LB_D
0x04 | immediate mode load to registers | _LDI
0x05 | copy register to another | _CPY 
0x06 | add registers | _ADD
0x07 | subtract registers | _SUB
0x08 | multiply registers | _MUL
0x09 | xor bitwise operation between registers | _XOR 
0x0A | and bitwise operation between registers | _AND
0x0B | or bitwise operation between registers | _OR
0x0C | comparison between registers | _CMP
0x0D | unconditional jump | _JMP
0x0E | jump if zero flag is 1 | _JZ
0x0F | jump if zero flag is not 1 | _JNZ
0x10 | jump if zf==0 and signf==1 | _JL
0x11 | jump if zf==0 and signf==0 | _JG
0x12 | jump if signf==1 | _JLE
0x13 | jump if signf==0 | _JGE
0x14 | store A register to memory address | _STR_A
0x15 | store B register to memory address | _STR_B
0x16 | store C register to memory address | _STR_C
0x17 | store D register to memory address | _STR_D


**Example:**

    0x14,0xff,0xff 
it stores the 8-bit value inside of the A register to 0xffff address

--------------------------------------------------------------------------------------------- 

### Memory Layout

we load our program to 0x00 address

#### **THIS SECTION IS NOT IMPLEMENTED YET**
  - I designed that cpu architecture as an embedded system thing. so it has mmio addresses which controls outside pins

Address | Description
--- | ---
0xFFFF | PINGROUP A
0xFFFE | PINGROUP B
0xFFFD | PINGROUP C
0xFFFC | PINGROUP D

Each address will control 8 pins etc... , its not decided yet.









