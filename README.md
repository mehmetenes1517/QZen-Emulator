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
FLAGS | 8 bit | overflow, carry , zero bits | 0x04
AB | 16 bit | Program counter | 0x05
CD | 16 bit | Program counter | 0x06
PC | 16 bit | Program counter | 0x07

**Memory Size :** 64 kilo bytes


### Instruction Set
---------------------------------------------------------------------------------------------

Instruction | Purpose | Machine Code Macro | Instruction sequence size
--- | --- | --- | ---
0x00 | load memory to A register | _LB_A | 3 
0x01 | load memory to B register | _LB_B | 3
0x02 | load memory to C register | _LB_C | 3
0x03 | load memory to D register | _LB_D | 3
0x04 | immediate mode load to registers | _LDI | 3
0x05 | copy register to another | _CPY | 3 
0x06 | add registers | _ADD | 3
0x07 | subtract registers | _SUB | 3
0x08 | multiply registers | _MUL | 3
0x09 | add registers with carry | _ADDC | 3
0x0A | xor bitwise operation between registers | _XOR | 3 
0x0B | and bitwise operation between registers | _AND | 3
0x0C | or bitwise operation between registers | _OR | 3
0x0D | increase register by 1 | _INC | 2
0x0E | decrease register by 1 | _DEC | 2
0x0F | comparison between registers | _CMP | 3
0x10| unconditional jump | _JMP | 3
0x11 | jump if zero flag is 1 | _JZ | 3
0x12 | jump if zero flag is not 1 | _JNZ | 3
0x13 | jump if zf==0 and signf==1 | _JL | 3
0x14 | jump if zf==0 and signf==0 | _JG | 3
0x15 | jump if signf==1 | _JLE | 3
0x16 | jump if signf==0 | _JGE | 3
0x17 | store A register to given 16bit memory address | _STRI_A | 3
0x18 | store B register to given 16bit memory address | _STRI_B | 3
0x19 | store C register to given 16bit memory address | _STRI_C | 3
0x1A | store D register to given 16bit memory address | _STRI_D | 3
0X1B | store given register's value as taking AB register's value as address | _STR_AB | 2 
0X1C | store given register's value as taking CD register's value as address | _STR_CD | 2 



**Example:**

    0x14,0xff,0xff 

 - it stores the 8-bit value inside of the A register to 0xffff address

    0x0d , 0x00

 - it increases A register by 1

--------------------------------------------------------------------------------------------- 

### Memory Layout

we load our program to 0x00 address

#### **THIS SECTION IS NOT IMPLEMENTED YET**

- I decided to make an 280x130 framebuffer in specific memory address interval

