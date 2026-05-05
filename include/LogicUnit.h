#pragma once
#include <cstdint>
struct ALU{
    void _add_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _sub_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _cmp_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _addc_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _mul_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _xor_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _and_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _or_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _dec_(uint8_t& reg1,uint8_t& flags);
    void _inc_(uint8_t& reg1,uint8_t& flags);
};
