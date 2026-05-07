#pragma once
#include<cstdint>
namespace _Register8{
    constexpr uint8_t _A=0x00;
    constexpr uint8_t _B=0x01;
    constexpr uint8_t _C=0x02;
    constexpr uint8_t _D=0x03;
    constexpr uint8_t _FLAGS=0x04;
    constexpr uint8_t _X=0x05;
    constexpr uint8_t _Y=0x06;
};
namespace _Register16{
    constexpr uint8_t _AB=0x00;
    constexpr uint8_t _CD=0x01;
    constexpr uint8_t _XY=0x02;
    constexpr uint8_t _PC=0x03;
    constexpr uint8_t _BP=0x04;
    constexpr uint8_t _SP=0x05;
}