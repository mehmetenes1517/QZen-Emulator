#include"../include/Main.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <raylib.h>





int main(){


    ControlUnit cpu(1000,false);  

    const char* animation_code=R"(
        start:
            ldi A, 0xFF
            ldi B, 0xFE
            ldi C, 0xFF
            ldi D, 0x00

        reset:
            ldi Y, 0x71
            ldi X, 0xCF

        draw_loop:
            str XY, C

            push X
            push A
            pop X
        delay_loop:
            dec X
            cmp X, D
            jnz delay_loop
            pop X

            inc X
            addc Y, D

            cmp Y, A
            jl draw_loop
            cmp X, B
            jle draw_loop

            cmp C, D
            jnz set_zero

        set_ff:
            push A
            pop C
            jmp reset

        set_zero:
            push D
            pop C
            jmp reset

        halt:
            jmp halt
    )";

    cpu.LoadProgram(AssembleText(animation_code,false));
    auto thr=std::thread([&](){
        cpu.Run();
    });
    thr.detach();
    
    std::array<const uint8_t*,280*130> framebuffer;
    for (size_t i = 0; i < (36400); i++)
    {
        framebuffer[i]=&cpu.memory.data[i+0x71CF];
    }
    int offsetx=10;
    int offsety=10;
    InitWindow(1500,700,"QZen - Framebuffer");
    while (!WindowShouldClose() || cpu.memory.data[0xffff]&1 != 1)
    {
        BeginDrawing();
        ClearBackground(GRAY);
    
        for(int i=0;i<130;++i){
            for(int j=0;j<280;++j){
                uint8_t color=*framebuffer[i*280+j];
                DrawRectangle(offsetx+j*3,offsety+i*3,3,3,Color{.r=color,.g=color,.b=color,.a=255});
            }
        }
        DrawText(std::string("A : "+std::to_string(cpu.AB.low)).c_str(),910, 0, 24, BLACK);
        DrawText(std::string("B : "+std::to_string(cpu.AB.high)).c_str(),910, 20, 24, BLACK);
        DrawText(std::string("C : "+std::to_string(cpu.CD.low)).c_str(),910, 40, 24, BLACK);
        DrawText(std::string("D : "+std::to_string(cpu.CD.high)).c_str(),910, 60, 24, BLACK);
        DrawText(std::string("AB : "+std::format("{:x}",cpu.XY.value)).c_str(),910, 80, 24, BLACK);
        DrawText(std::string("CD : "+std::format("{:x}",cpu.XY.value)).c_str(),910, 100, 24, BLACK);
        DrawText(std::string("XY : "+std::format("{:x}",cpu.XY.value)).c_str(),910, 120, 24, BLACK);
        DrawText(std::string("Flags : "+std::to_string(cpu.FLAGS)).c_str(),910, 140, 24, BLACK);
        DrawText(std::string("Program Counter : "+std::to_string(cpu.PC.value)).c_str(),910, 160, 24, BLACK);
        DrawText(std::string("Base Pointer : "+std::format("{:x}",cpu.BP.value)).c_str(),910, 180, 24, BLACK);
        DrawText(std::string("Stack Pointer : "+std::format("{:x}",cpu.SP.value)).c_str(),910, 200, 24, BLACK);
        

        EndDrawing();
    }
    cpu.memory.Display();
    cpu.memory.write(0xffff,0xff);
    CloseWindow();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));



    return 0;
}

