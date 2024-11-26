#include "asm.hpp"

void AppendInstrArgType(Cmds* command_cpu_code, ArgType arg_type) {
    assert(command_cpu_code != nullptr);
    *(char*)command_cpu_code |= (char)arg_type;
}

void SetCommandTypeBitCode(ArgType* old_arg_type, ArgType new_arg_type) {
    assert(old_arg_type != NULL);
    *(char*)old_arg_type |= (char)new_arg_type;
}

bool AsmCompiler::IsLabel(Instruction& instr, std::string label) {
    for(size_t i = 0; i < labels.size(); i++) {        
        if(label == labels[i].name) {
            instr.arg = static_cast<double>(labels[i].address);
            return true;
        }
    }
    return false;
}

bool AsmCompiler::IsReg(Instruction& instr, std::string reg) {
    #define REG_DEF(reg_name, reg_cpu_code)      \
        if(#reg_name == reg)  {                   \
            instr.arg = reg_cpu_code;              \
            return true;                            \
        }                                    
    #include "../utils/regs.hpp"
    #undef REG_DEF
    return false;
}

int IsCommand(Instruction& command, std::string cmd_name, int& arg_num) {
    assert(arg_num ==0 || arg_num == 1);
    #define DEF_CMD(name, cpu_code, args_num, ...)        \
        if(cmd_name == #name) {                            \
            command.cmd = (Cmds)cpu_code;                   \
            arg_num = args_num;                              \
            return 1;                                         \
        }
            
    #include "../utils/cmds.hpp"
    #undef DEF_CMD
    return 0;
}

void AsmCompiler::SetInstruction(Instruction& instr, 
                                 std::string cmd_name, 
                                 ArgType arg_type)    {
    int arg_num = 0;
    if(!IsCommand(instr, cmd_name, arg_num)) {
        return;
    }

    AppendInstrArgType(&(instr.cmd), arg_type); 
    
    assert(cmd_name != "POP" || arg_type != IMM);
    assert((arg_type == NOARG && arg_num == 0) ||
           (arg_type != NOARG && arg_num == 1));
    instructions.push_back(instr);
}

void AsmCompiler::ReadLine(std::istringstream& cur_str, 
                          Instruction& instr)          {
    std::string cmd_name;
    std::string str;

    cur_str >> cmd_name;
    if(cur_str >> str) {
        if(IsReg(instr, str)) {
            SetInstruction(instr, cmd_name, REG);
        }
        else if(IsLabel(instr, str)) {
            SetInstruction(instr, cmd_name, LAB);
        }
        else {
            instr.arg = std::stod(str);
            SetInstruction(instr, cmd_name, IMM);
        }
    }
    else {
        if(cmd_name[cmd_name.size() - 1] != ':') {
            instr.arg = 0;
            SetInstruction(instr, cmd_name, NOARG);
        }
    }
}

void AsmCompiler::Execute(std::string wfile_name) {
    Instruction command;

    std::ofstream file(wfile_name, std::ios::binary);
    assert(file);

    int blank_lines_counter = 0;

    int lines_size = lines.size();
    for(int line_num = 1; line_num < lines_size + 1; ++line_num) {
        std::istringstream cur_str(lines[line_num - 1]);
		std::string label_name;

        if(cur_str >> label_name ) { 
            if(!(cur_str >> label_name)) {
                if(label_name[label_name.size() - 1] == ':') {
                    label_name.pop_back();
                    Label new_label(label_name, line_num - labels.size() - blank_lines_counter);
                    labels.push_back(new_label);
                }
            }
        }
        else {
            blank_lines_counter++;
        }
    }

    for(int line_num = 1; line_num <= lines_size; ++line_num) {
        std::istringstream cur_str(lines[line_num - 1]);
        ReadLine(cur_str, command);
    }

    int instructions_size = instructions.size();

    for(int i = 0; i < instructions_size; ++i) {
        file.write(reinterpret_cast<char*>(&instructions[i]), sizeof(Instruction));
    }
    file.close();
}

void AsmCompiler::ReadFile(std::ifstream& file) {
    assert(file);
    std::string line;
    while(std::getline(file, line)) {
        lines.push_back(line);
    }
}

AsmCompiler::AsmCompiler(std::string rfile_name) {
    std::ifstream file(rfile_name);
    assert(file);
    ReadFile(file);
    file.close();
}

