#pragma once
#include<cstdint>
namespace Instruction{
    constexpr uint8_t _LB_A=0X00; 
    constexpr uint8_t _LB_B=0X01; 
    constexpr uint8_t _LB_C=0X02; 
    constexpr uint8_t _LB_D=0X03; 
    constexpr uint8_t _LDI=0X04; 
    constexpr uint8_t _CPY=0X05; 
    constexpr uint8_t _ADD=0X06; 
    constexpr uint8_t _SUB=0X07; 
    constexpr uint8_t _MUL=0X08; 
    constexpr uint8_t _ADDC=0X09; 
    constexpr uint8_t _XOR=0X0A; 
    constexpr uint8_t _AND=0X0B; 
    constexpr uint8_t _OR=0X0C; 
    constexpr uint8_t _INC=0X0D; 
    constexpr uint8_t _DEC=0X0E; 
    constexpr uint8_t _CMP=0X0F; 
    constexpr uint8_t _JMP=0X10; 
    constexpr uint8_t _JZ=0X11; 
    constexpr uint8_t _JNZ=0X12; 
    constexpr uint8_t _JL=0X13; 
    constexpr uint8_t _JG=0X14; 
    constexpr uint8_t _JLE=0X15; 
    constexpr uint8_t _JGE=0X16; 
    constexpr uint8_t _STRI_A=0X17; 
    constexpr uint8_t _STRI_B=0X18; 
    constexpr uint8_t _STRI_C=0X19; 
    constexpr uint8_t _STRI_D=0X1A; 
    constexpr uint8_t _STR_AB=0X1B; 
    constexpr uint8_t _STR_CD=0X1C; 
};