#pragma once
#include<iostream>
#include<vector>
#include<cstdint>
#include<fstream>
#include"../Register16.h"
std::vector<uint8_t> AssembleText(const std::string& filename,bool opendebug);
uint8_t Register8FromToken(const std::string& token);
Register16 AddressFromToken(const std::string& token);
