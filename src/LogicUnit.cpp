#include "../include/LogicUnit.h"
#include"../include/Util.h"
void ALU::_add_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val=reg1+reg2;
    if(val < reg1){SetCarryFlag(flags);}
    reg1=val;
}

void ALU::_sub_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val=reg1-reg2;
    if(val==0){SetZeroFlag(flags);}
    if(reg1 < reg2){SetCarryFlag(flags);}
    reg1=val;
}

void ALU::_cmp_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    if(reg1 == reg2){SetZeroFlag(flags);}
    if(reg1 < reg2){SetCarryFlag(flags);}
}

void ALU::_addc_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    uint8_t c = GetCarryFlag(flags);
    ResetFlags(flags);
    uint16_t temp = (uint16_t)reg1 + reg2 + c;
    if(temp > 0xFF){SetCarryFlag(flags);}
    reg1 = (uint8_t)temp;
}

void ALU::_mul_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint16_t multipication=uint16_t(reg1)*uint16_t(reg2); 
    if(multipication==0){SetZeroFlag(flags);}
    reg1=multipication&0xff;
    reg2=multipication>>8;
}   

void ALU::_xor_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val =reg1^reg2;
    if(val==0){SetZeroFlag(flags);}
    reg1=val;
}

void ALU::_and_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val =reg1&reg2;
    if(val==0){SetZeroFlag(flags);}
    reg1=val;
}

void ALU::_or_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val =reg1|reg2;
    if(val==0){SetZeroFlag(flags);}
    reg1=val;
}

void ALU::_dec_(uint8_t& reg1,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val=reg1-1;
    if(val==0){SetZeroFlag(flags);}
    reg1=val;
}

void ALU::_inc_(uint8_t& reg1,uint8_t& flags){
    ResetFlags(flags);
    uint8_t val=reg1+1;
    if(val==0){SetCarryFlag(flags);}
    reg1=val;   
}