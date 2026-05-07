#include "../include/Memory.h"
void Memory::write(uint16_t address,uint8_t data){
     this->data[address]=data;
}
uint8_t Memory::read(uint16_t address) const{
     return data[address];
 }
void Memory::Display() const{
     std::cout<<"\n*************************************************\n";
     std::cout<<"\n\t\tMemory\t\t\n";
     std::cout<<"\n*************************************************\n";
     for(size_t i=0;i<data.max_size();i++){
         if(i%(0x0fff)==0){
             std::cout<<"\n";
         }
         std::cout<<std::setw(2)<<" "<<std::hex<<int(data[i]);
     }
 }
