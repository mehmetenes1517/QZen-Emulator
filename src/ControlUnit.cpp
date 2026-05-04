#include "../include/ControlUnit.h"
#include"../include/Util.h"
ControlUnit::ControlUnit(float frequency,bool debug_on):frequency_hz(frequency),debugmode(debug_on){
    Restart();
}
void ControlUnit::Restart(){
    A=B=C=D=0x00;
    PC=0X0000;
    memory.data.fill(0x00);
}
void ControlUnit::LoadProgram(const std::vector<uint8_t>& instructions){
    for(size_t i=0;i<instructions.size();i++){
        memory.write(i,instructions[i]);
    }
}
uint8_t ControlUnit::Fetch(){
    return memory.data[PC++];
}
void ControlUnit::Decode_Execute(uint8_t command){
    //COMMAND DECODE
    switch (command) {
        case 0x00:{
            ld_a_from_address();
            break;
        }case 0x01:{
            ld_b_from_address();
            break;
        }case 0x02:{
            ld_c_from_address();
            break;
        }case 0x03:{
            ld_d_from_address();
            break;
        }case 0x04:{
            immediate_load();
            break;
        }case 0x05:{
            copy_register();
            break;
        }case 0x06:{
            AddRegs();
            break;
        }case 0x07:{
            SubRegs();
            break;
        }case 0x08:{
            break;
        }case 0x09:{
            break;
        }case 0x0A:{
            break;
        }case 0x0B:{
            break;
        }case 0x0C:{
            CmpRegs();
            break;
        }case 0x0D:{
            Jump();
            break;
        }case 0x0E:{
            Jump_zero();
            break;
        }case 0x0F:{
            Jump_nonzero();
            break;
        }case 0x10:{
            Jump_Less();
            break;
        }case 0x11:{
            Jump_Greater();
            break;
        }case 0x12:{
            Jump_LessEqual();
            break;
        }case 0x13:{
            Jump_GreaterEqual();
            break;
        }case 0x14:{
            str_a_to_address();
            break;
        }case 0x15:{
            str_b_to_address();
            break;
        }case 0x16:{
            str_c_to_address();
            break;
        }case 0x17:{
            str_d_to_address();
            break;
        }
        default:{
            break;
        }
    }
    //MMIO OPERATIONS
    if((memory.data[0xff]&0x01)==1){
        Restart();
    }


}
void ControlUnit::Run(){
    while (PC<memory.data.size() ){
        uint8_t command=Fetch();
        Decode_Execute(command);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0f*(1.0f/frequency_hz))));
    }
}
void ControlUnit::ld_a_from_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    A=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_b_from_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    B=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_c_from_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    C=memory.read(ByteConcat(upper,lower));

}
void ControlUnit::ld_d_from_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    D=memory.read(ByteConcat(upper,lower));

}
void ControlUnit::immediate_load(){
    uint8_t& reg=DecodeRegister(*this,memory.read(PC++));
    uint8_t value=memory.read(PC++);
    reg=value;

}
void ControlUnit::copy_register(){
    uint8_t& reg1=DecodeRegister(*this,memory.read(PC++));
    uint8_t& reg2=DecodeRegister(*this,memory.read(PC++));
    reg1=reg2;

}

void ControlUnit::AddRegs(){
    uint8_t& reg1=DecodeRegister(*this,memory.read(PC++));
    uint8_t& reg2=DecodeRegister(*this,memory.read(PC++));
    alu._add_(reg1,reg2,FLAGS);
}
void ControlUnit::SubRegs(){
    uint8_t& reg1=DecodeRegister(*this,memory.read(PC++));
    uint8_t& reg2=DecodeRegister(*this,memory.read(PC++));
    alu._sub_(reg1,reg2,FLAGS);
}
void ControlUnit::CmpRegs(){
    uint8_t& reg1=DecodeRegister(*this,memory.read(PC++));
    uint8_t& reg2=DecodeRegister(*this,memory.read(PC++));
    alu._cmp_(reg1,reg2,FLAGS);
}

void ControlUnit::Jump(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    std::cout<<"\nJUMP ADDRESS "<<ByteConcat(upper,lower)<<std::flush;
    PC=ByteConcat(upper,lower);

}
void ControlUnit::Jump_zero(){
    if((FLAGS&1)==1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_nonzero(){
    if((FLAGS&(1))!=1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_Less(){
    if(((FLAGS>>1)&(1))==1 && ((FLAGS)&(1))==0){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_LessEqual(){
    if(((FLAGS>>1)&(1))==1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_Greater(){
    if(((FLAGS>>1)&(1))==0 && ((FLAGS)&(1))==0){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_GreaterEqual(){
    if(((FLAGS>>1)&(1))==0){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::str_a_to_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,A);
}
void ControlUnit::str_b_to_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,B);
}
void ControlUnit::str_c_to_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,C);
}
void ControlUnit::str_d_to_address(){
    uint8_t upper=memory.read(PC++);
    uint8_t lower=memory.read(PC++);
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,D);
}
        