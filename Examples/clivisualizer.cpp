#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include "../include/ControlUnit.h"
int main(){

    ControlUnit cu(5,false);
    //Example program
    // start:
    // mov A,5
    // mov B,1
    // mov C,26
    // add:
    // add A <- A+B
    // cmp A,C
    // jnz add:
    cu.LoadProgram({
        0xf1,5,//mov a,5
        0xf2,1,//mov b,1
        0xf3,26,//mov c,1
        0xf9,//add a,b
        0xe2,//cmp a,c
        0xe0,0x06,//jump to add a,b line
        0xf0,0x0a //jump to same line
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
        ss<<std::setw(60)<<("\n\033[34mMemory 0xff : ")<<(int(cu.memory.data[0xff]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfe : ")<<(int(cu.memory.data[0xfe]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfd : ")<<(int(cu.memory.data[0xfd]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfc : ")<<(int(cu.memory.data[0xfc]));
        ss<<std::setw(60)<<("\n\033[31mFlags : ")<<int(cu.FLAGS);
        ss<<std::setw(60)<<("\n\033[31mProgram Counter : ")<<int(cu.PC);
        ss<<std::setw(60)<<"\n\033[33m*****************************************\n\033[0m";
        ss<<std::flush;
        std::cout<<ss.str();
    }
    
    
    


    return 0;
}
