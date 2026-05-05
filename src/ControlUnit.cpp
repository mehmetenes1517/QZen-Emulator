#include "../include/ControlUnit.h"
#include"../include/Util.h"
#include"../include/Instructions.h"
ControlUnit::ControlUnit(float frequency,bool debug_on):frequency_hz(frequency),debugmode(debug_on){
    Restart();
}
void ControlUnit::Restart(){
    A=B=C=D=0x00;
    PC=0X0000;
    ResetFlags(FLAGS);
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
        case _LB_A:{
            ld_a_from_address();
            break;
        }case _LB_B:{
            ld_b_from_address();
            break;
        }case _LB_C:{
            ld_c_from_address();
            break;
        }case _LB_D:{
            ld_d_from_address();
            break;
        }case _LDI:{
            immediate_load();
            break;
        }case _CPY:{
            copy_register();
            break;
        }case _ADD:{
            AddRegs();
            break;
        }case _SUB:{
            SubRegs();
            break;
        }case _MUL:{
            MulRegs();
            break;
        }case _ADDC:{
            AddCRegs();
            break;
        }case _XOR:{
            XORRegs();
            break;
        }case _AND:{
            ANDRegs();
            break;
        }case _OR:{
            ORRegs();
            break;
        }case _CMP:{
            CmpRegs();
            break;
        }case _INC:{
            INCReg();            
            break;
        }case _DEC:{
            DECReg();
            break;
        }case _JMP:{
            Jump();
            break;
        }case _JZ:{
            Jump_zero();
            break;
        }case _JNZ:{
            Jump_nonzero();
            break;
        }case _JL:{
            Jump_Less();
            break;
        }case _JG:{
            Jump_Greater();
            break;
        }case _JLE:{
            Jump_LessEqual();
            break;
        }case _JGE:{
            Jump_GreaterEqual();
            break;
        }case _STR_A:{
            str_a_to_address();
            break;
        }case _STR_B:{
            str_b_to_address();
            break;
        }case _STR_C:{
            str_c_to_address();
            break;
        }case _STR_D:{
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
    while (true){
        uint8_t command=Fetch();
        Decode_Execute(command);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0f*(1.0f/frequency_hz))));
        PC=PC%(0XFFFF+1);
    }
}
uint8_t ControlUnit::get_next_arg(){
    return memory.read(PC++);
}
void ControlUnit::ld_a_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    A=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_b_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    B=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_c_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    C=memory.read(ByteConcat(upper,lower));

}
void ControlUnit::ld_d_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    D=memory.read(ByteConcat(upper,lower));

}
void ControlUnit::immediate_load(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    uint8_t value=get_next_arg();
    reg=value;

}
void ControlUnit::copy_register(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    reg1=reg2;

}

void ControlUnit::AddRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._add_(reg1,reg2,FLAGS);
}
void ControlUnit::SubRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._sub_(reg1,reg2,FLAGS);
}
void ControlUnit::MulRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._mul_(reg1,reg2,FLAGS);
}
void ControlUnit::AddCRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._addc_(reg1,reg2,FLAGS);
}
void ControlUnit::XORRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._xor_(reg1,reg2,FLAGS);
}
void ControlUnit::ANDRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._and_(reg1,reg2,FLAGS);
}
void ControlUnit::ORRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._or_(reg1,reg2,FLAGS);
}
void ControlUnit::INCReg(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    alu._inc_(reg,FLAGS);
}
void ControlUnit::DECReg(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    alu._dec_(reg,FLAGS);
}
void ControlUnit::CmpRegs(){
    uint8_t& reg1=DecodeRegister(*this,get_next_arg());
    uint8_t& reg2=DecodeRegister(*this,get_next_arg());
    alu._cmp_(reg1,reg2,FLAGS);
}

void ControlUnit::Jump(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    std::cout<<"\nJUMP ADDRESS "<<ByteConcat(upper,lower)<<std::flush;
    PC=ByteConcat(upper,lower);
}
void ControlUnit::Jump_zero(){
    if(GetZeroFlag(FLAGS)==1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_nonzero(){
    if(GetZeroFlag(FLAGS)!=1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_Less(){
    if(GetCarryFlag(FLAGS)==1 && GetZeroFlag(FLAGS)==0){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_LessEqual(){
    if(GetCarryFlag(FLAGS)==1){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_Greater(){
    if(GetCarryFlag(FLAGS)==0 && GetZeroFlag(FLAGS)==0){
        Jump();
    }else{
        PC+=2;
    }
}
void ControlUnit::Jump_GreaterEqual(){
    if(GetCarryFlag(FLAGS)==0){
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