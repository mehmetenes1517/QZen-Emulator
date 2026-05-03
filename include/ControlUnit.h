#pragma once

#include "LogicUnit.h"
#include "Memory.h"
#include <chrono>
#include <cstdint>
#include <ios>
#include <iostream>
#include <thread>
#include <vector>

struct ControlUnit{
    float frequency_hz=2.0f;
    bool debugmode=true;
    uint8_t A=0x00,B=0x00,C=0x00,D=0x00;
    uint8_t PC=0x00;
    uint8_t FLAGS=0x00;// 0 -> zero flag , 1 -> carry flag , 2-> negative flag
    Memory memory;
    ALU alu;

    ControlUnit(float frequency,bool debug_on);
    void Restart();
    void LoadProgram(const std::vector<uint8_t>& instructions);
    uint8_t Fetch();
    void Decode_Execute(uint8_t command);
    void Run();

};
