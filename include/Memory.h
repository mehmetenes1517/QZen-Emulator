#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <iomanip>
constexpr int MEMORY_CAP=0xffff+1;


struct Memory{
    std::array<uint8_t,MEMORY_CAP> data;
    Memory()=default;
    void write(uint16_t address,uint8_t data);
    uint8_t read(uint16_t address) const;
    void Display() const;
};
