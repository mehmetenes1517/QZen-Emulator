#include"../../include/Main.h"
#include<assert.h>
#include<raylib.h>
int main(){

    std::vector<uint8_t> code=AssembleText(R"(
        start:
            ldi A,0x05
            ldi B,0x01
            ldi C,0x1A
        add11:
            add A,B
            cmp A,C
            jnz add11
            lb B,[0xffff]
            add A,B
            stri [0xffff], A
            jmp start
        )",false);
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
    while (true)
    {
        static std::stringstream ss;
        ss.str("");
        ss.clear();
        ss<<"\033[H";
        ss<<std::setw(60)<<"\033[33m********************************************\n";
        ss<<std::setw(60)<<("\n\033[32mA : ")<<int(cu.AB.low);
        ss<<std::setw(60)<<("\n\033[32mB : ")<<int(cu.AB.high);
        ss<<std::setw(60)<<("\n\033[32mC : ")<<int(cu.CD.low);
        ss<<std::setw(60)<<("\n\033[32mD : ")<<int(cu.CD.high);
        ss<<std::setw(60)<<("\n\033[34mMemory 0xffff : ")<<(int(cu.memory.data[0xffff]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffe : ")<<(int(cu.memory.data[0xfffe]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffd : ")<<(int(cu.memory.data[0xfffd]));
        ss<<std::setw(60)<<("\n\033[34mMemory 0xfffc : ")<<(int(cu.memory.data[0xfffc]));
        ss<<std::setw(60)<<("\n\033[31mFlags : ")<<int(cu.FLAGS);
        ss<<std::setw(60)<<("\n\033[31mProgram Counter : ")<<int(cu.PC.value);
        ss<<std::setw(60)<<"\n\033[33m*****************************************\n\033[0m";
        ss<<std::flush;
        std::cout<<ss.str();
    }
    

    return 0;
}

