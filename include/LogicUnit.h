#pragma once
#include <cstdint>
struct ALU{
    void _add_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _sub_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
    void _cmp_(uint8_t& reg1,uint8_t& reg2,uint8_t& flags);
};
