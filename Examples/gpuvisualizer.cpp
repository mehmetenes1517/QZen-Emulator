#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <thread>
#include <raylib.h>
#include "../include/ControlUnit.h"
int main(){

    ControlUnit cu(5,true);
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
    InitWindow(800, 600, "CPU Visualizer");
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText(std::string("A : "+std::to_string(cu.A)).c_str(),10, 0, 24, BLACK);
            DrawText(std::string("B : "+std::to_string(cu.B)).c_str(),10, 20, 24, BLACK);
            DrawText(std::string("C : "+std::to_string(cu.C)).c_str(),10, 40, 24, BLACK);
            DrawText(std::string("D : "+std::to_string(cu.D)).c_str(),10, 60, 24, BLACK);
            DrawText(std::string("Memory 0xff : "+std::to_string(cu.memory.data[0xff])).c_str(),10, 80, 24, BLACK);
            DrawText(std::string("Memory 0xfe : "+std::to_string(cu.memory.data[0xfe])).c_str(),10, 100, 24, BLACK);
            DrawText(std::string("Memory 0xfd : "+std::to_string(cu.memory.data[0xfd])).c_str(),10, 120, 24, BLACK);
            DrawText(std::string("Memory 0xfc : "+std::to_string(cu.memory.data[0xfc])).c_str(),10, 140, 24, BLACK);
            DrawText(std::string("Flags : "+std::to_string(cu.FLAGS)).c_str(),10, 160, 24, BLACK);
            DrawText(std::string("Program Counter : "+std::to_string(cu.PC)).c_str(),10, 180, 24, BLACK);


        EndDrawing();
    }

    return 0;
}
