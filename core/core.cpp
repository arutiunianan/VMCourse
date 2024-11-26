#include "core.hpp"

Cmds ClearInstrArgType(Cmds command_code, ArgType arg_type) {
    return (Cmds)(command_code & ~arg_type);
}

bool IsValidRegArg(Instruction instr) {
    bool is_reg_found = false;

    switch((size_t)instr.arg)
    {
        #define REG_DEF(name, cpu_code, ...)   \
        case cpu_code:                          \
            is_reg_found = true;                 \
            break;

        #include "../utils/regs.hpp"
    }
    #undef REG_DEF
    
    if(!is_reg_found)
    {
        return false;
    }

    return true;
}

void Core::SetReg(Elem_t reg, Elem_t value) {
    switch((int)reg)
    {
        #define REG_DEF(reg_name, reg_value)     \
        case reg_name:                            \
            registers.reg_name = value;            \
            return;                                 \
            break;                                 

        #include "../utils/regs.hpp"
        #undef REG_DEF
    }
}

Elem_t Core::GetValidArgument(ArgType arg_type, Instruction& istr) {
    if(arg_type == IMM || arg_type == LAB)
    {
        return istr.arg;
    }
    else if(arg_type == REG)
    {
        switch((int)istr.arg)
        {
            #define REG_DEF(reg_name, reg_value)       \
                case reg_value:                         \
                    return registers.reg_name;           \

            #include "../utils/regs.hpp"
            #undef REG_DEF
        }
    }
}

bool IsValidCommand(Instruction& instr, ArgType& arg_type) {
    int arg_num = 0;

    if((char)instr.cmd & REG && instr.cmd != HLT) {
        arg_type = REG;

        if(!IsValidRegArg(instr)) {
            return false;
        }
        arg_num = 1;
    }
    else if((char)instr.cmd & IMM && instr.cmd != HLT) {
        arg_type = IMM;
            
        if(instr.cmd == POP)
        {
            return false;
        }
        arg_num = 1;
    }
    else if((char)instr.cmd & LAB && instr.cmd != HLT) {
        arg_type = LAB;

        arg_num = 1;
    }
    else if(instr.arg != 0) {
        return false;
    }

    switch(ClearInstrArgType(instr.cmd, arg_type)) {
        #define DEF_CMD(cmd_name, cmd_num, cmd_n_args, cmd_code)    \
        case cmd_name:                                               \
            return (arg_num == cmd_n_args);
        
        #include "../utils/cmds.hpp"

        default:
            return 0;
    }
    #undef DEF_CMD
}

void Core::ReadFile(std::ifstream& file) {
    assert(file);
    Instruction instr;
    while (file.read(reinterpret_cast<char*>(&instr), sizeof(Instruction))) {
        instructions.push_back(instr);
    }
}

Core::Core(std::string file_name) {
    std::ifstream file(file_name);
    assert(file);
    ReadFile(file);
    file.close();
}

int Core::Execute() {
    int instructions_num = instructions.size();
    Frame frame;
    for(current_line = 1; current_line < instructions_num + 1; ++current_line) {
        Instruction instr = instructions[current_line - 1];

        ArgType arg_type = NOARG;

        if(IsValidCommand(instr, arg_type)) {
            switch(ClearInstrArgType(instr.cmd, arg_type)) {
                #define DEF_CMD(cmd_name, cmd_num, cmd_n_args, cmd_code)    \
                case cmd_name:                                               \
                    cmd_code;                                                 \
                    break;
                
                #include "../utils/cmds.hpp"
                #undef DEF_CMD
            }
        }
        else {
            std::cerr << "Invalid command or argument" << std::endl;
            return;
        }
    }
}
