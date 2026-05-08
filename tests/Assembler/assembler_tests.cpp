#include"../../include/Main.h"
#include<assert.h>
#include<raylib.h>
int main(){

    std::vector<uint8_t> code=AssembleText(R"(
        start:
            ldi A,0x00
            ldi B,0x06
        add:
            inc A
            cmp A,B
            jl add            
        halt1:
            jmp halt1
        )",true);

    assert((6*3)==code.size());
    std::cout<<std::format("\n\033[32m[Passed] Code size is matching!\n\033[0m");

    



    return 0;
}

