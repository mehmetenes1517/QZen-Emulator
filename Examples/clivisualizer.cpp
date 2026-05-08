#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "../include/Main.h"
int main(){

    std::vector<uint8_t> code=AssembleText(R"(
        start:
            ldi A,0xff
            ldi C,0x00
        add11:
            inc C
            cmp C,A
            jl add11
            
            ldi A,0x01
            stri [0xffff],A
        halt:
            jmp halt
        )");
    ControlUnit cu(100,false);


    cu.LoadProgram(code);
    
    auto thr=std::thread([&](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cu.Run();
    });
    thr.detach();
    while ((cu.memory.data[0xffff]&1) != 1)
    {
        static std::stringstream ss;
        ss.str("");
        ss.clear();
        ss<<"\033[H";
        ss<<std::setw(60)<<"\033[33m********************************************\n";
        ss<<std::setw(60)<<("\n\033[32mA : 0x")<<std::hex<<int(cu.AB.low);
        ss<<std::setw(60)<<("\n\033[32mB : 0x")<<std::hex<<int(cu.AB.high);
        ss<<std::setw(60)<<("\n\033[32mC : 0x")<<std::hex<<int(cu.CD.low);
        ss<<std::setw(60)<<("\n\033[32mD : 0x")<<std::hex<<int(cu.CD.high);
        ss<<std::setw(60)<<("\n\033[32mX : 0x")<<std::hex<<int(cu.XY.low);
        ss<<std::setw(60)<<("\n\033[32mY : 0x")<<std::hex<<int(cu.XY.high);
        ss<<std::setw(60)<<("\n\033[31mFlags : 0x")<<std::hex<<int(cu.FLAGS);
        ss<<std::setw(60)<<("\n\033[31mProgram Counter : 0x")<<std::hex<<int(cu.PC.value);
        ss<<std::setw(60)<<"\n\033[33m*****************************************\n\033[0m";
        ss<<std::flush;
        std::cout<<ss.str();
    }
    cu.memory.Display();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    
    return 0;
}
