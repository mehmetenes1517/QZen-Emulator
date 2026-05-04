#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "../include/Main.h"
int main(){

    ControlUnit cu(10,false);
    //Example program
    // start:
    // ldi A,5
    // ldi B,1
    // ldi C,26
    // add:
    // add A <- A+B
    // cmp A,C
    // jle add:
    // lb B,[0xffff]
    // add A,B
    // str [0xffff], A
    // jmp 0x0000
    cu.LoadProgram({
        _LDI,_A,5,
        _LDI,_B,1,
        _LDI,_C,26,
        _ADD,_A,_B,
        _CMP,_A,_C,
        _JLE,0x00,0x09,
        _LB_B,0xFF,0xFF,
        _ADD,_A,_B,
        _STR_A,0xFF,0xFF,
        _JMP,0x00,0x00
    });
    auto thr=std::thread([&](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cu.Run();
    });
    thr.detach();
    while (true)
    {
        static std::stringstream ss;
        ss.str("");
        ss.clear();
        ss<<"\033[H";
        ss<<std::setw(60)<<"\033[33m********************************************\n";
        ss<<std::setw(60)<<("\n\033[32mA : ")<<int(cu.A);
        ss<<std::setw(60)<<("\n\033[32mB : ")<<int(cu.B);
        ss<<std::setw(60)<<("\n\033[32mC : ")<<int(cu.C);
        ss<<std::setw(60)<<("\n\033[32mD : ")<<int(cu.D);
        ss<<std::setw(60)<<("\n\033[34mMemory 0xffff : ")<<(int(cu.memory.data[0xffff]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffe : ")<<(int(cu.memory.data[0xfffe]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffd : ")<<(int(cu.memory.data[0xfffd]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffc : ")<<(int(cu.memory.data[0xfffc]));
        ss<<std::setw(60)<<("\n\033[31mFlags : ")<<int(cu.FLAGS);
        ss<<std::setw(60)<<("\n\033[31mProgram Counter : ")<<int(cu.PC);
        ss<<std::setw(60)<<"\n\033[33m*****************************************\n\033[0m";
        ss<<std::flush;
        std::cout<<ss.str();
    }
    
    
    


    return 0;
}
