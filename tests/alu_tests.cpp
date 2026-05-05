#include"../include/Main.h"
#include<assert.h>
int main(){
    ALU alu;
    uint8_t flags=0x00;
    uint8_t A=0xff;  
    uint8_t B=0xff; 



    ResetFlags(flags); //0x00
    alu._add_(A,B,flags);
    assert(GetCarryFlag(flags)==1);
    std::cout<<"\n\033[32m [Passed] Addition overflow test!\033[0m";
    assert(A==(0xfe));
    std::cout<<"\n\033[32m [Passed] Addition result test!\033[0m";


    A=0x00;
    B=0x0f;
    ResetFlags(flags); //0x00
    alu._sub_(A,B,flags);
    assert(GetCarryFlag(flags)==1);
    std::cout<<"\n\033[32m [Passed] Subtraction negativity test!\n\033[0m";
    assert(A==uint8_t(0x00-0x0f));
    std::cout<<"\n\033[32m [Passed] Subtraction result test!\n\033[0m";


    A=0xff;
    B=0xff;
    ResetFlags(flags); //0x00
    alu._mul_(A,B,flags);
    uint16_t result=uint16_t(0x00ff)*uint16_t(0x00ff);
    uint8_t lower_bits=result&0xff;
    uint8_t upper_bits=result>>8;
    assert(A==(lower_bits));
    assert(B==(upper_bits));
    std::cout<<"\n\033[32m [Passed] Multipication result test!\033[0m";
    
    A=0xff;
    ResetFlags(flags);
    alu._xor_(A,A,flags);
    assert(A==0x00);
    std::cout<<"\n\033[32m [Passed] XOR result test!\033[0m";

    A=0x00;
    B=0xff;
    ResetFlags(flags);
    alu._or_(A,B,flags);
    assert(A==0xff);
    std::cout<<"\n\033[32m [Passed] OR result test!\033[0m";
    
    A=0xff;
    B=0x00;
    ResetFlags(flags);
    alu._and_(A,B,flags);
    assert(A==0x00);
    std::cout<<"\n\033[32m [Passed] AND result test!\033[0m";

    
    A=0xff;
    B=0xff;
    ResetFlags(flags);
    alu._add_(A,B,flags);
    alu._addc_(A,B,flags);
    assert(A==0xfe && GetCarryFlag(flags));
    std::cout<<"\n\033[32m [Passed] add with carry result test!\033[0m";

    assert(uint16_t(9) == ByteConcat(0x00,0x09));
    std::cout<<"\n\033[32m[Passed] Byte Concatination test!\n\033[0m";

}