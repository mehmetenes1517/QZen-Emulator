#pragma once
#include<cstdint>
union Register16
{
    uint16_t value;
    struct{
        uint8_t low;
        uint8_t high;
    };
};
using Value16=Register16;
