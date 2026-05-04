#include "../include/LogicUnit.h"
void ALU::_add_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags=0x00;
    uint8_t value=reg1+reg2;
    if(value==0){//zero bit
        flags|=(1<<0);
    }
    if(value<reg1 || value<reg2){//overflow
        flags|=(1<<2);
    }
    reg1=value;
}
void ALU::_sub_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags=0x00;
    uint8_t value=reg1-reg2;
    if(value==0){//zero bit
        flags|=(1<<0);
    }
    if(value>reg1 || value>reg2){//sign bit (negative)
        flags|=(1<<1);
    }
    reg1=value;
}
void ALU::_cmp_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags=0x00;
    uint8_t value=reg1-reg2;
    if(value==0){// zero bit
        flags|=(1<<0);
    }if(value>reg1 || value>reg2){//sign bit (negative)
        flags|=(1<<1);
    }
}
