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
    private:
        uint8_t get_next_arg();
        void ld_a_from_address();
        void ld_b_from_address();
        void ld_c_from_address();
        void ld_d_from_address();
        void str_a_to_address();
        void str_b_to_address();
        void str_c_to_address();
        void str_d_to_address();
        void immediate_load();
        void copy_register();
        void Jump();
        void Jump_zero();
        void Jump_nonzero();
        void Jump_Less();
        void Jump_LessEqual();
        void Jump_Greater();
        void Jump_GreaterEqual();
        void AddRegs();
        void SubRegs();
        void MulRegs();
        void AddCRegs();
        void XORRegs();
        void ANDRegs();
        void ORRegs();
        void INCReg();
        void DECReg();
        void CmpRegs();
    public:
        friend uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value);

    float frequency_hz=2.0f;
    bool debugmode=true;
    uint8_t A=0x00,B=0x00,C=0x00,D=0x00;
    uint8_t PC=0x00;
    uint8_t FLAGS=0x00;// 0 -> zero bit , 1 -> sign bit , 2-> overflow bit
    Memory memory;
    ALU alu;

    ControlUnit(float frequency,bool debug_on);
    void Restart();
    void LoadProgram(const std::vector<uint8_t>& instructions);
    uint8_t Fetch();
    void Decode_Execute(uint8_t command);
    void Run();

};
