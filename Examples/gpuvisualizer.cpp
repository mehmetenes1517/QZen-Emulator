#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <thread>
#include <raylib.h>
#include "../include/Main.h"
int main(){

    ControlUnit cu(100,true);
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
        _LDI,_C,26,
        _INC,_A,
        _CMP,_A,_C,
        _JLE,0x00,0x06,
        _LB_B,0xFF,0xFF,
        _ADD,_A,_B,
        _STR_A,0xFF,0xFF,
        _XOR,_B,_B,
        _JMP,0x00,0x00
    });

    auto thr=std::thread([&](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cu.Run();
    });
    thr.detach();
    InitWindow(800, 600, "CPU Visualizer");
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText(std::string("A : "+std::to_string(cu.A)).c_str(),10, 0, 24, BLACK);
            DrawText(std::string("B : "+std::to_string(cu.B)).c_str(),10, 20, 24, BLACK);
            DrawText(std::string("C : "+std::to_string(cu.C)).c_str(),10, 40, 24, BLACK);
            DrawText(std::string("D : "+std::to_string(cu.D)).c_str(),10, 60, 24, BLACK);
            DrawText(std::string("Memory 0xffff : "+std::to_string(cu.memory.data[0xffff])).c_str(),10, 80, 24, BLACK);
            DrawText(std::string("Memory 0xfffe : "+std::to_string(cu.memory.data[0xfffe])).c_str(),10, 100, 24, BLACK);
            DrawText(std::string("Memory 0xfffd : "+std::to_string(cu.memory.data[0xfffd])).c_str(),10, 120, 24, BLACK);
            DrawText(std::string("Memory 0xfffc : "+std::to_string(cu.memory.data[0xfffc])).c_str(),10, 140, 24, BLACK);
            DrawText(std::string("Flags : "+std::to_string(cu.FLAGS)).c_str(),10, 160, 24, BLACK);
            DrawText(std::string("Program Counter : "+std::to_string(cu.PC)).c_str(),10, 180, 24, BLACK);


        EndDrawing();
    }

    return 0;
}
