#include"../include/Util.h"
#include"../include/ControlUnit.h"
uint16_t ByteConcat(uint8_t upper,uint8_t lower){
    uint16_t val=0x0000;
    val|=upper<<8;
    val|=lower;
    return val;
}
uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value){
    switch (encoded_value)
    {
    case 0x00:
        return obj.A;
        break;
    case 0x01:
        return obj.B;
        break;
    case 0x02:
        return obj.C;
        break;
    case 0x03:
        return obj.D;
        break;
    case 0x04:
        return obj.PC;
        break;
    case 0x05:
        return obj.FLAGS;    
        break;
    }
}