#include "../include/LogicUnit.h"
void ALU::_add_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags &= ~(7);
    if((static_cast<uint8_t>(reg1+reg2))<reg1){
        flags |= (1<<1);
    }else{
         flags &= ~(1<<1);
    }
    reg1+=reg2;
}
void ALU::_sub_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags &= ~(7);
    if(reg1==reg2){
        flags |= (1<<0);
    }else{
         flags &= ~(1<<0);
    }
    if(reg1<reg2){
        flags |= (1<<2);
    }else{
         flags &= ~(1<<2);
    }

    reg1-=reg2;

}
void ALU::_cmp_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags){
    flags &= ~(0b111);
    if((reg1-reg2)==0){
        flags |= (1<<0);
    }else if((reg1-reg2)<0){
        flags |= (1<<2);
    }
}
