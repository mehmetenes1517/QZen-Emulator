#pragma once
#include<cstdint>
class ControlUnit;
uint16_t ByteConcat(uint8_t upper,uint8_t lower);
uint8_t& DecodeRegister(ControlUnit& obj,uint8_t encoded_value);