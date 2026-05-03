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

Register | Size | Info 
--- | --- | ---
A | 8 bit | General Purpose
B | 8 bit | General Purpose
C | 8 bit | General Purpose
D | 8 bit | General Purpose
PC | 8 bit | Program counter
FLAGS | 8 bit | zero,signed,carry bits

**Memory Size :** 256 bytes



### Instruction Set
---------------------------------------------------------------------------------------------

Instruction | Purpose
--- | ---
0xF0 | jmp -> address
0xF1 | mov A -> value
0xF2 | mov B -> value
0xF3 | mov C -> value
0xF4 | mov D -> value
0xF5 | mov A -> address
0xF6 | mov B -> address
0xF7 | mov C -> address
0xF8 | mov D -> address
0xF9 | add A, B 
0xFA | add A, C
0xFB | add A, D
0xFC | sub A, B
0xFD | sub A, C
0xFE | sub A, D
0xFF | jz -> address
0xE0 | jnz -> address
0xE1 | cmp A,B
0xE2 | cmp A,C
0xE3 | cmp A,D

**Note :** The instructions i write as '->' are requires second operand 

**Example:**

    0xF5 0XFF 
it moves the 8-bit value inside of the 0xff address to our A register  

--------------------------------------------------------------------------------------------- 

### Memory Layout

we load our program to 0x00 address

#### **THIS SECTION IS NOT IMPLEMENTED YET**
  - I designed that cpu architecture as an embedded system thing. so it has mmio addresses which controls outside pins

Address | Description
--- | ---
0xFF | PINGROUP A
0xFE | PINGROUP B
0xFD | PINGROUP C
0xFC | PINGROUP D

Each address will control 8 pins etc... , its not decided yet.









