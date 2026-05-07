#include"../../include/Main.h"
#include<assert.h>

int main(){

    std::vector<uint8_t> code=AssembleText("main.s",false);
    for(const auto& b:code){
        std::cout<<"\n"<<std::hex<<int(b);
    }

}