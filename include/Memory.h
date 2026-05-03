#pragma once
#include <array>
#include <cstdint>
#include <iostream>
#include <iomanip>
constexpr int MEMORY_CAP=256;


struct Memory{
    std::array<uint8_t,MEMORY_CAP> data;
    Memory()=default;
    void write(uint8_t address,uint8_t data);
    uint8_t read(uint8_t address) const;
    void Display() const;
};
