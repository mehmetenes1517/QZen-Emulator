#pragma once
#include<cstdint>
#include<iostream>
class ControlUnit;
uint16_t ByteConcat(uint8_t upper,uint8_t lower);
uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value);
uint8_t GetZeroFlag(uint8_t flag_register);
uint8_t GetSignFlag(uint8_t flag_register);
uint8_t GetCarryFlag(uint8_t flag_register);
void SetZeroFlag(uint8_t& flag_register);
void SetSignFlag(uint8_t& flag_register);
void SetCarryFlag(uint8_t& flag_register);
void ResetZeroFlag(uint8_t& flag_register);
void ResetSignFlag(uint8_t& flag_register);
void ResetCarryFlag(uint8_t& flag_register);
void ResetFlags(uint8_t& flag_register);
namespace String{
    std::string ToLower(const std::string& text);
};