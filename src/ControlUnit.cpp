#include "../include/ControlUnit.h"
#include"../include/Util.h"
#include"../include/Instructions.h"
ControlUnit::ControlUnit(float frequency,bool debug_on):frequency_hz(frequency),debugmode(debug_on){
    Restart();
}
void ControlUnit::Restart(){
    AB=CD=XY={0x0000};
    PC={0X0000};
    BP={0x71CD};
    SP={0x71CD};
    ResetFlags(FLAGS);
    memory.data.fill(0x00);
}
void ControlUnit::LoadProgram(const std::vector<uint8_t>& instructions){
    for(size_t i=0;i<instructions.size();i++){
        memory.write(i,instructions[i]);
    }
}
uint8_t ControlUnit::Fetch(){
    return memory.data[PC.value++];
}
void ControlUnit::Decode_Execute(uint8_t command){
    //COMMAND DECODE
    switch (command) {
        case Instruction::_LB_A:{
            ld_a_from_address();
            break;
        }case Instruction::_LB_B:{
            ld_b_from_address();
            break;
        }case Instruction::_LB_C:{
            ld_c_from_address();
            break;
        }case Instruction::_LB_D:{
            ld_d_from_address();
            break;
        }case Instruction::_LB_X:{
            ld_x_from_address();
            break;
        }case Instruction::_LB_Y:{
            ld_y_from_address();
            break;
        }case Instruction::_LDI:{
            immediate_load();
            break;
        }case Instruction::_CPY:{
            copy_register();
            break;
        }case Instruction::_ADD:{
            AddRegs();
            break;
        }case Instruction::_SUB:{
            SubRegs();
            break;
        }case Instruction::_MUL:{
            MulRegs();
            break;
        }case Instruction::_ADDC:{
            AddCRegs();
            break;
        }case Instruction::_XOR:{
            XORRegs();
            break;
        }case Instruction::_AND:{
            ANDRegs();
            break;
        }case Instruction::_OR:{
            ORRegs();
            break;
        }case Instruction::_CMP:{
            CmpRegs();
            break;
        }case Instruction::_INC:{
            INCReg();            
            break;
        }case Instruction::_DEC:{
            DECReg();
            break;
        }case Instruction::_JMP:{
            Jump();
            break;
        }case Instruction::_JZ:{
            Jump_zero();
            break;
        }case Instruction::_JNZ:{
            Jump_nonzero();
            break;
        }case Instruction::_JL:{
            Jump_Less();
            break;
        }case Instruction::_JG:{
            Jump_Greater();
            break;
        }case Instruction::_JLE:{
            Jump_LessEqual();
            break;
        }case Instruction::_JGE:{
            Jump_GreaterEqual();
            break;
        }case Instruction::_STRI_A:{
            str_a_to_immediate_address();
            break;
        }case Instruction::_STRI_B:{
            str_b_to_immediate_address();
            break;
        }case Instruction::_STRI_C:{
            str_c_to_immediate_address();
            break;
        }case Instruction::_STRI_D:{
            str_d_to_immediate_address();
            break;
        }case Instruction::_STR_AB:{
            str_ab();
            break;
        }case Instruction::_STR_CD:{
            str_cd();
            break;
        }case Instruction::_STR_XY:{
            str_xy();
            break;
        }case Instruction::_PUSH:{
            Push_Register();
            break;
        }case Instruction::_POP:{
            Pop_Register();
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
        PC.value=PC.value%(0XFFFF+1);
    }
}
uint8_t ControlUnit::get_next_arg(){
    return memory.read(PC.value++);
}
void ControlUnit::ld_a_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    AB.low=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_b_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    AB.high=memory.read(ByteConcat(upper,lower));
}
void ControlUnit::ld_c_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    CD.low=memory.read(ByteConcat(upper,lower));

}
void ControlUnit::ld_d_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    CD.high=memory.read(ByteConcat(upper,lower));

}void ControlUnit::ld_x_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    XY.low=memory.read(ByteConcat(upper,lower));

}void ControlUnit::ld_y_from_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    XY.high=memory.read(ByteConcat(upper,lower));

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
    PC.value++; //FOR ALIGNMENT
    alu._inc_(reg,FLAGS);
}
void ControlUnit::DECReg(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
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
    if(debugmode){
        std::cout<<"\nJUMP ADDRESS "<<ByteConcat(upper,lower)<<std::flush;
    }
    PC.value=ByteConcat(upper,lower);
}
void ControlUnit::Jump_zero(){
    if(GetZeroFlag(FLAGS)==1){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::Jump_nonzero(){
    if(GetZeroFlag(FLAGS)!=1){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::Jump_Less(){
    if(GetCarryFlag(FLAGS)==1 && GetZeroFlag(FLAGS)==0){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::Jump_LessEqual(){
    if(GetCarryFlag(FLAGS)==1){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::Jump_Greater(){
    if(GetCarryFlag(FLAGS)==0 && GetZeroFlag(FLAGS)==0){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::Jump_GreaterEqual(){
    if(GetCarryFlag(FLAGS)==0){
        Jump();
    }else{
        PC.value+=2;
    }
}
void ControlUnit::str_a_to_immediate_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,AB.low);
}
void ControlUnit::str_b_to_immediate_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,AB.high);
}
void ControlUnit::str_c_to_immediate_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,CD.low);
}
void ControlUnit::str_d_to_immediate_address(){
    uint8_t upper=get_next_arg();
    uint8_t lower=get_next_arg();
    uint16_t address=ByteConcat(upper,lower);
    memory.write(address,CD.high);
}
void ControlUnit::str_cd(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
    memory.write(CD.value,reg);
}
void ControlUnit::str_ab(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
    memory.write(AB.value,reg);
}
void ControlUnit::str_xy(){
    uint8_t& reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
    memory.write(XY.value,reg);
}
void ControlUnit::Push_Register(){
    uint8_t &reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
    memory.write(SP.value--,reg);
}
void ControlUnit::Pop_Register(){
    uint8_t &reg=DecodeRegister(*this,get_next_arg());
    PC.value++; //FOR ALIGNMENT
    reg=memory.read(++SP.value);
}