#include"../include/Main.h"
#include<iostream>
#include<raylib.h>





int main(){


    ControlUnit cpu(1000,false);

    const char* line_code=R"(
        start:
            ldi X,0xfe
            ldi Y,0xef
            ldi D,0x01
            ldi C,0xA5
            ldi A,0x00
        ADDXY:
            ldi D,0x01

            add X,D
            xor D,D
            addc Y,D
            ldi D,0xff
            str XY,D
            inc A
            cmp A,C
            jle ADDXY


            jmp start
        func1:
            add X,D
            xor D,D
            addc Y,D
            ldi D,0xff
            str XY,D
            jmp func1_return 
    )";

    const char* test_code=R"(
        start:
            ldi A,0x15
            ldi B,0x10

            jmp func1
            func1_return:


        halt:
            jmp halt
        func1:
            add A,B
            jmp func1_return
    )";
    //its trying to replace func1 label and cant find it , its replacing not found label with 0x0000 

    cpu.LoadProgram(AssembleText(test_code));
    auto thr=std::thread([&](){
        cpu.Run();
    });
    thr.detach();
    
    std::array<const uint8_t*,280*130> framebuffer;
    for (size_t i = 0; i < (280*130); i++)
    {
        framebuffer[i]=&cpu.memory.data[i+0x71CE];
    }
    int offsetx=10;
    int offsety=10;
    InitWindow(1500,700,"QZen - Framebuffer");
    while (!WindowShouldClose() || cpu.memory.data[0xffff]&1 != 1)
    {
        BeginDrawing();
        ClearBackground(GRAY);
    
        for(int i=129;i>=0;--i){
            for(int j=279;j>=0;--j){
                uint8_t color=*framebuffer[i*280+j];
                DrawRectangle(offsetx+j*3,offsety+i*3,3,3,Color{.r=color,.g=color,.b=color,.a=255});
            }
        }
        DrawText(std::string("A : "+std::to_string(cpu.AB.low)).c_str(),910, 0, 24, BLACK);
        DrawText(std::string("B : "+std::to_string(cpu.AB.high)).c_str(),910, 20, 24, BLACK);
        DrawText(std::string("C : "+std::to_string(cpu.CD.low)).c_str(),910, 40, 24, BLACK);
        DrawText(std::string("D : "+std::to_string(cpu.CD.high)).c_str(),910, 60, 24, BLACK);
        DrawText(std::string("X : "+std::to_string(cpu.XY.low)).c_str(),910, 80, 24, BLACK);
        DrawText(std::string("Y : "+std::to_string(cpu.XY.high)).c_str(),910, 100, 24, BLACK);
        DrawText(std::string("Flags : "+std::to_string(cpu.FLAGS)).c_str(),910, 120, 24, BLACK);
        DrawText(std::string("Program Counter : "+std::to_string(cpu.PC.value)).c_str(),910, 140, 24, BLACK);
        

        EndDrawing();
    }
    cpu.memory.Display();
    CloseWindow();
    sleep(1);



    return 0;
}

