#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <thread>
#include <raylib.h>
#include "../include/Main.h"
int main(){

    std::vector<uint8_t> code=AssembleText(R"(
        start:
            ldi A,0x05
            ldi B,0x01
            ldi C,0x1A
            push C
            pop B
            add A,B
            push A
            pop C
            stri [0xffff],C
            halt:
            jmp halt
        )");
    ControlUnit cu(100,true);
    //Example program
    //start:
    //    ldi A,0x05
    //    ldi B,0x01
    //    ldi C,0x1A
    //add11:
    //    add A,B
    //    cmp A,C
    //    jnz add11
    //    lb B,[0xffff]
    //    add A,B
    //    stri [0xffff], A
    //    jmp start
    cu.LoadProgram(code);

    auto thr=std::thread([&](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cu.Run();
    });
    thr.detach();
    InitWindow(800, 600, "CPU Visualizer");
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText(std::string("A : "+std::to_string(cu.AB.low)).c_str(),10, 0, 24, BLACK);
            DrawText(std::string("B : "+std::to_string(cu.AB.high)).c_str(),10, 20, 24, BLACK);
            DrawText(std::string("C : "+std::to_string(cu.CD.low)).c_str(),10, 40, 24, BLACK);
            DrawText(std::string("D : "+std::to_string(cu.CD.high)).c_str(),10, 60, 24, BLACK);
            DrawText(std::string("Memory 0xffff : "+std::to_string(cu.memory.data[0xffff])).c_str(),10, 80, 24, BLACK);
            DrawText(std::string("Memory 0xfffe : "+std::to_string(cu.memory.data[0xfffe])).c_str(),10, 100, 24, BLACK);
            DrawText(std::string("Memory 0xfffd : "+std::to_string(cu.memory.data[0xfffd])).c_str(),10, 120, 24, BLACK);
            DrawText(std::string("Memory 0xfffc : "+std::to_string(cu.memory.data[0xfffc])).c_str(),10, 140, 24, BLACK);
            DrawText(std::string("Flags : "+std::to_string(cu.FLAGS)).c_str(),10, 160, 24, BLACK);
            DrawText(std::string("Program Counter : "+std::to_string(cu.PC.value)).c_str(),10, 180, 24, BLACK);


        EndDrawing();
    }

    return 0;
}
