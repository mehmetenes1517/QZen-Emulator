#include"../include/Main.h"

int main(){

    if(9 != ByteConcat(0x00,0x09)){
        std::cout<<"\033[31m[FAILED] Byte Concatination is working!\n";
        return -1;
    }std::cout<<"\033[32m[PASSED] Byte Concatination is working!\n";
}