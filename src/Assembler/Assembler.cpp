#include"../../include/Assembler/Assembler.h"
#include"../../include/Registers.h"
#include"../../include/Instructions.h"
#include"../../include/Util.h"
#include<iostream>
#include<unordered_map>
std::vector<uint8_t> AssembleText(const std::string& assembly_code,bool opendebug){

    //tokenize it
    std::vector<std::string> tokens;
    tokens.reserve(1024);
    {

        std::string token;
        for (size_t i = 0; i < assembly_code.size(); i++)
        {
            if( assembly_code[i]!=',' && assembly_code[i]!='\n' && !std::isspace(assembly_code[i])){
                token.push_back(assembly_code[i]);
                
            }else if(token.size()!=0){
                tokens.push_back(token);
                token.clear();
            }
        }
        if(opendebug){
            std::cout<<"\nTOKEN COUNT : "<<tokens.size()<<std::flush;
        }
    }   

    //lexer
    std::vector<uint8_t> code;
    std::unordered_map<std::string,uint8_t> address_table;//address table for labels
    for(size_t i=0;i<tokens.size();i++){
        if(opendebug){
            std::cout<<"\nToken : "+tokens[i]<<std::flush;
        }
        //labels
        if(tokens[i].back()==':'){
            tokens[i].pop_back();
            address_table[tokens[i]]=(i==0)?(0):(i-1);
            if(opendebug){
                std::cout<<"\nLabel Address : "<<std::hex<<int(address_table[tokens[i]])<<std::flush;
            }
        }
        //indirect load "lb A,[0xffff]" 
        else if(tokens[i]=="lb"){
            uint8_t instruction=Register8FromToken(tokens[++i]); 
            Register16 src=AddressFromToken(tokens[++i]);
            switch (instruction)
            {
            case Instruction::_LB_A:
                instruction=0x00;
                break;
            case Instruction::_LB_B:
                instruction=0x01;
                break;
            case Instruction::_LB_C:
                instruction=0x02;
                break;
            case Instruction::_LB_D:
                instruction=0x03;
                break;
            }
            code.push_back(instruction);
            code.push_back(src.high);          
            code.push_back(src.low);          
        }
        //immidiate load "lb A,0xffff" 
        else if(tokens[i]=="ldi"){
            uint8_t register_arg=Register8FromToken(tokens[++i]);
            Register16 value=ValueFromToken(tokens[++i]);
            code.push_back(Instruction::_LDI);
            code.push_back(register_arg);
            code.push_back(value.low);
        }
        //register copy "cpy A,B" 
        else if(tokens[i]=="cpy"){
            uint8_t register_arg1=Register8FromToken(tokens[++i]);
            uint8_t register_arg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_CPY);
            code.push_back(register_arg1);
            code.push_back(register_arg2);
        }
        //unconditional jump "jmp label" 
        else if(tokens[i]=="jmp"){
            std::string label=(tokens[++i]);
            Register16 address={address_table[label]};
            code.push_back(Instruction::_JMP);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //add regs "add A,B" 
        else if(tokens[i]=="add"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_ADD);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //subtract regs "sub A,B" 
        else if(tokens[i]=="sub"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_SUB);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //multiply regs "mul A,B" 
        else if(tokens[i]=="mul"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_MUL);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //add with carry regs "addc A,B" 
        else if(tokens[i]=="addc"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_ADDC);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //xor regs "xor A,B" 
        else if(tokens[i]=="xor"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_XOR);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //and regs "and A,B" 
        else if(tokens[i]=="and"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_AND);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //or regs "and A,B" 
        else if(tokens[i]=="or"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_OR);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //increment by 1 "inc A" 
        else if(tokens[i]=="inc"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_INC);
            code.push_back(reg1);
            code.push_back(0xff);
        }
        //decrement by 1 "dec A" 
        else if(tokens[i]=="dec"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_DEC);
            code.push_back(reg1);
            code.push_back(0xff);
        }
        //compare regs "cmp A,B" 
        else if(tokens[i]=="cmp"){
            uint8_t reg1=Register8FromToken(tokens[++i]);
            uint8_t reg2=Register8FromToken(tokens[++i]);
            code.push_back(Instruction::_CMP);
            code.push_back(reg1);
            code.push_back(reg2);
        }
        //jump if zero "jz label" 
        else if(tokens[i]=="jz"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JZ);
            code.push_back(address.high);
            code.push_back(address.low);

        }
        //jump if not zero "jnz label" 
        else if(tokens[i]=="jnz"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JNZ);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //jump if less "jl label" 
        else if(tokens[i]=="jl"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JL);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //jump if greater "jg label" 
        else if(tokens[i]=="jg"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JG);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //jump if less equal "jle label" 
        else if(tokens[i]=="jle"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JLE);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //jump if greater or equal "jge label" 
        else if(tokens[i]=="jge"){
            std::string token=tokens[++i];
            Value16 address={address_table[token]};
            code.push_back(Instruction::_JGE);
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //store from given immediate address "str [0xfffe],A" 
        else if(tokens[i]=="stri"){
            Value16 address={AddressFromToken(tokens[++i])};
            uint8_t register_code=Register8FromToken(tokens[++i]);
            if(register_code==_Register8::_A){
                code.push_back(Instruction::_STRI_A);
            }
            else if(register_code==_Register8::_B){
                code.push_back(Instruction::_STRI_B);
            }
            else if(register_code==_Register8::_C){
                code.push_back(Instruction::_STRI_C);
            }
            else if(register_code==_Register8::_D){
                code.push_back(Instruction::_STRI_D);
            }
            code.push_back(address.high);
            code.push_back(address.low);
        }
        //store to "str [0xfffe],A" 
        else if(tokens[i]=="str"){
            uint8_t register16_code=Register16FromToken(tokens[++i]);
            uint8_t register8_code=Register8FromToken(tokens[++i]);
            if(register16_code==_Register16::_AB){
                code.push_back(Instruction::_STR_AB);
            }
            if(register16_code==_Register16::_CD){
                code.push_back(Instruction::_STR_CD);
            }
            code.push_back(register8_code);
            code.push_back(0xff);
        }
        else{
            throw std::runtime_error("Invalid Instruction! "+ tokens[i]);
        }
    }
    return code;
}
uint8_t  Register8FromToken(const std::string& token){
    std::string token_lower=String::ToLower(token);
    if      (token_lower=="a"){return _Register8::_A;}
    else if (token_lower=="b"){return _Register8::_B;}
    else if (token_lower=="c"){return _Register8::_C;}
    else if (token_lower=="d"){return _Register8::_D;}

    throw std::runtime_error("Invalid Argument! "+token);
}
uint8_t  Register16FromToken(const std::string& token){
    std::string token_lower=String::ToLower(token);
    if      (token_lower=="ab"){return _Register16::_AB;}
    else if (token_lower=="cd"){return _Register16::_CD;}
    else if (token_lower=="pc"){throw std::runtime_error("Invalid Argument! Program counter cannot be used as memory store");}
    throw std::runtime_error("Invalid Argument! "+token);
}
Register16 AddressFromToken(const std::string& token){
    if(token.front()=='[' && token.back()==']'){
        std::string tk;
        for(size_t i=0;i<token.size();i++){
            if(i>0 && i<(token.size()-1)){
                tk.push_back(token[i]);
            }
        }
        Register16 address={uint16_t(std::stoi(tk,0,16))};
        return address;
    }
    throw std::runtime_error("Invalid Argument - expected an address ! "+token);
}
Register16 ValueFromToken(const std::string& token){
    if(token.front()!='[' && token.back()!=']'){
        Register16 address={uint16_t(std::stoi(token,0,16))};
        return address;
    }
    throw std::runtime_error("Invalid Argument - expected a value ! "+token);
}
