#include "../include/ControlUnit.h"
ControlUnit::ControlUnit(float frequency,bool debug_on):frequency_hz(frequency),debugmode(debug_on){
    Restart();
}
void ControlUnit::Restart(){
    A=B=C=D=PC=0x00;
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
        case 0xf0:{// jump to address unconditionally
            PC=memory.data[PC];
            if(debugmode){
                std::cout<<"\nJUMP 0x"<<std::hex<<int(PC)<<std::flush;
            }
            break;
        }
        case 0xf1:{//mov value to A register
            A=memory.data[PC];
            if(debugmode){
                std::cout<<"\nMOV A, "<<std::hex<<int(A)<<"\n"<<std::flush;
            }
            PC++;
            break;
        }
        case 0xf2:{//mov value to B register
            B=memory.data[PC];
            if(debugmode){
                std::cout<<"\nMOV B, "<<int(memory.data[PC])<<std::flush;
            }
            PC++;
            break;
        }
        case 0xf3:{//mov value to C register
            C=memory.data[PC];
            if(debugmode){
                std::cout<<"\nMOV C, "<<int(memory.data[PC])<<std::flush;
            }
            PC++;
            break;
        }
        case 0xf4:{//mov value to D register
            D=memory.data[PC];
            if(debugmode){
                std::cout<<"\nMOV D, "<<int(memory.data[PC])<<std::flush;
            }
            PC++;
            break;
        }
        case 0xf5:{//mov A Register to address
            memory.write(memory.read(PC), A);
            PC++;
            break;
        }
        case 0xf6:{//mov B Register to address
            memory.write(memory.read(PC), B);
            PC++;
            break;
        }
        case 0xf7:{//mov C Register to address
            memory.write(memory.read(PC), C);
            PC++;
            break;
        }
        case 0xf8:{//mov D Register to address
            memory.write(memory.read(PC), D);
            PC++;
            break;
        }
        case 0xf9:{//add A register with B store in A
            alu._add_(A, B,FLAGS);
            if(debugmode){
                std::cout<<"\nADD A,B"<<std::flush;
            }
            break;
        }
        case 0xfa:{//add A register with C store in A
            alu._add_(A, C,FLAGS);
            if(debugmode){
                std::cout<<"\nADD A,C"<<std::flush;
            }
            break;
        }
        case 0xfb:{//add A register with D store in A
            alu._add_(A, D,FLAGS);
            if(debugmode){
                std::cout<<"\nADD A,D"<<std::flush;
            }
            break;
        }
        case 0xfc:{//subtract B register from A store in A
            alu._sub_(A, B,FLAGS);
            if(debugmode){
                std::cout<<"\nSUB A,B"<<std::flush;
            }
            break;
        }
        case 0xfd:{//subtract C register from A store in A
            alu._sub_(A, C,FLAGS);
            if(debugmode){
                std::cout<<"\nSUB A,C"<<std::flush;
            }
            break;
        }
        case 0xfe:{//subtract D register from A store in A
            alu._sub_(A, C,FLAGS);
            if(debugmode){
                std::cout<<"\nSUB A,D"<<std::flush;
            }
            break;
        }
        case 0xff:{// jump if zero flag is 1
            if((FLAGS&0x01) == 1){
                PC=memory.data[PC];
                if(debugmode){
                    std::cout<<"\nCONDTITONAL JUMP 0x"<<std::hex<<int(PC)<<std::flush;
                }
            }else{
                PC++;
            }
            break;
        }
        case 0xe0:{//jump if zero flag is not 1
            if((FLAGS&0x01) != 1){
                PC=memory.read(PC);
                if(debugmode){
                    std::cout<<"\nCONDITIONAL JUMP 0x"<<std::hex<<int(PC)<<std::flush;
                }
            }else{
                PC++;
            }
            break;
        }
        case 0xe1:{// compare A with B
            alu._cmp_(A, B, FLAGS);
            if(debugmode){
                std::cout<<"\nCompare A B"<<std::flush;
            }
            break;
        }
        case 0xe2:{// compare A with C
            alu._cmp_(A, C, FLAGS);
            if(debugmode){
                std::cout<<"\nCompare A C"<<std::flush;
            }
            break;
        }
        case 0xe3:{// compare A with D
            alu._cmp_(A, D, FLAGS);
            if(debugmode){
                std::cout<<"\nCompare A D"<<std::flush;
            }
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
