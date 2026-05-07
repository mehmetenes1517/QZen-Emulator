#pragma once

#include "LogicUnit.h"
#include "Memory.h"
#include "Register16.h"
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
        void ld_x_from_address();
        void ld_y_from_address();
        void str_a_to_immediate_address();
        void str_b_to_immediate_address();
        void str_c_to_immediate_address();
        void str_d_to_immediate_address();
        void str_cd();
        void str_ab();
        void str_xy();
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
        void Push_Register();
        void Pop_Register();
    public:
        friend uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value);

    float frequency_hz=2.0f;
    bool debugmode=true;
    Register16 AB={0x0000},CD={0x0000},XY={0x00};
    Register16 PC={0x0000};
    Register16 BP={0x71CD},SP={0x71CD};
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

