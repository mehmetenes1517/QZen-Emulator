## Qzen-Emulator

a 8-bit cpu architecture which i made up , it has 2 examples inside that visualizes registers, Framebuffer etc..


-------------------------------------------------------------------------------------------

**Examples/FrameBufferVisualizer** --> If you have raylib installed on your compiler , you can build it , its a framebuffer animation demo

**Examples/CLIVisualizer** --> Portable cli of visualizer , there is no framebuffer, just registers

-------------------------------------------------------------------------------------------

### Build

building GPU accelerated visualizer 

    cmake -B build/
    cmake --build build/ --target FrameBufferVisualizer

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
X | 8 bit | General Purpose | 0x05
Y | 8 bit | General Purpose | 0x06
AB | 16 bit | General Purpose | 0x00
CD | 16 bit | General Purpose | 0x01
XY | 16 bit | General Purpose | 0x02
PC | 16 bit | Program counter | 0x03
BP | 16 bit | Base Pointer | 0x04
SP | 16 bit | Stack Pointer | 0x05


### Instruction Set
---------------------------------------------------------------------------------------------

Instruction | Purpose | Code Macro | Instruction sequence size | Assembly code
--- | --- | --- | --- | ---
0x00 | load memory to A register | _LB_A | 3 | lb
0x01 | load memory to B register | _LB_B | 3 | lb
0x02 | load memory to C register | _LB_C | 3 | lb
0x03 | load memory to D register | _LB_D | 3 | lb
0x1F | load memory to D register | _LB_X | 3 | lb
0x20 | load memory to D register | _LB_Y | 3 | lb
0x04 | immediate mode load to registers | _LDI | 3 | ldi
0x05 | copy register to another | _CPY | 3  | cpy
0x06 | add registers | _ADD | 3 | add
0x07 | subtract registers | _SUB | 3 | sub
0x08 | multiply registers | _MUL | 3 | mul
0x09 | add registers with carry | _ADDC | 3 | addc
0x0A | xor bitwise operation between registers | _XOR | 3 | xor
0x0B | and bitwise operation between registers | _AND | 3 | and
0x0C | or bitwise operation between registers | _OR | 3 | or
0x0D | increase register by 1 | _INC | 2 | inc
0x0E | decrease register by 1 | _DEC | 2 | dec
0x0F | comparison between registers | _CMP | 3 | cmp
0x10| unconditional jump | _JMP | 3 | jmp
0x11 | jump if zero flag is 1 | _JZ | 3 | jz
0x12 | jump if zero flag is not 1 | _JNZ | 3 | jnz
0x13 | jump if carryf==1 and zerof==0 | _JL | 3 | jl
0x14 | jump if carryf==0 and zerof==0 | _JG | 3 | jg
0x15 | jump if carryf==1 or zerof==1 | _JLE | 3 | jle
0x16 | jump if carryf==0 or zerof==1 | _JGE | 3 | jge
0x17 | store A register to given 16bit memory address | _STRI_A | 3 | stri
0x18 | store B register to given 16bit memory address | _STRI_B | 3 | stri
0x19 | store C register to given 16bit memory address | _STRI_C | 3 | stri
0x1A | store D register to given 16bit memory address | _STRI_D | 3 | stri
0x21 | store D register to given 16bit memory address | _STRI_X | 3 | stri
0x22 | store D register to given 16bit memory address | _STRI_Y | 3 | stri
0X1B | store given register's value as taking AB register's value as address | _STR_AB | 2 | str
0X1C | store given register's value as taking CD register's value as address | _STR_CD | 2 | str
0X23 | store given register's value as taking XY register's value as address | _STR_XY | 2 | str
0X1D | push given register's value to stack | _PUSH | 2 | push
0X1E | pop from stack to a register | _POP | 2 | pop



**Example:**

        0x14,0xff,0xff 

 - it stores the 8-bit value inside of the A register to 0xffff address

        0x0d,0x00,0xff

 - it increases A register by 1

**Important Note :**
 - In 2 byte instructions , you should align the instruction sequence to 3 bytes with padding it with <code>0xff</code>


--------------------------------------------------------------------------------------------- 

### Memory Layout

- we load our program to 0x00 address

- and in <code>Examples/Framebuffer</code> , there is a framebuffer in specific interval and a kill switch address which ends the cpu loop 

        0xFFFF -> control byte(kill switch)

        0XFFFE-> fb end 
        0x71CF-> fb start

        0x71CE-> base pointer
        0x71CE-> stack pointer


        0x0000-> program entry point
