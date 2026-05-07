#include"../include/Util.h"
#include"../include/ControlUnit.h"
#include"../include/Registers.h"
uint16_t ByteConcat(uint8_t upper,uint8_t lower){
    uint16_t val=0x0000;
    val|=upper<<8;
    val|=lower;
    return val;
}
uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value){
    switch (encoded_value)
    {
        
    case _Register8::_A:
        return obj.AB.low;
        break;
    case _Register8::_B:
        return obj.AB.high;
        break;
    case _Register8::_C:
        return obj.CD.low;
        break;
    case _Register8::_D:
        return obj.CD.high;
        break;
    }
    throw std::runtime_error("Cannot decode value !"+std::to_string(encoded_value));  
}

uint8_t GetZeroFlag(uint8_t flag_register){return flag_register&1;}
uint8_t GetSignFlag(uint8_t flag_register){return (flag_register>>1)&1;}
uint8_t GetCarryFlag(uint8_t flag_register){return (flag_register>>2)&1;}
void SetZeroFlag(uint8_t& flag_register){ flag_register|= (1<<0);}
void SetSignFlag(uint8_t& flag_register){ flag_register|= (1<<1);}
void SetCarryFlag(uint8_t& flag_register){flag_register|= (1<<2);}
void ResetZeroFlag(uint8_t& flag_register){ flag_register&= ~(1<<0);}
void ResetSignFlag(uint8_t& flag_register){ flag_register&= ~(1<<1);}
void ResetCarryFlag(uint8_t& flag_register){flag_register&= ~(1<<2);}
void ResetFlags(uint8_t& flag_register){flag_register=0x00;}




//string utility

std::string String::ToLower(const std::string& text){
    std::string lowertext;
    lowertext.reserve(256);
    for(const auto& c: text){
        lowertext.push_back(std::tolower(c));
    }
    return lowertext;
}
