#include "asm.hpp"

static const int NUM_OF_LABLES = 20; 
static const int MAX_STRLEN = 1024;
static const int MAX_CMDSIZE = 256;

void AppendInstrArgType(Cmds* command_cpu_code, ArgType arg_type)
{
    *(char*)command_cpu_code |= (char)arg_type;
}

void SetCommandTypeBitCode(ArgType* old_arg_type, ArgType new_arg_type)
{
    *(char*)old_arg_type |= (char)new_arg_type;
}

bool AsmCompiler::IsLabel(Instruction& instr, std::string label)
{
    for(size_t i = 0; i < labels.size(); i++)
    {        
        if(label == labels[i].name)
        {
            instr.arg = static_cast<double>(labels[i].address);
            return true;
        }
    }
    return false;
}

bool AsmCompiler::IsReg(Instruction& instr, std::string reg)
{
    #define REG_DEF(reg_name, reg_cpu_code)     \
        if(#reg_name == reg)                     \
        {                                         \
            instr.arg = reg_cpu_code;              \
            return true;                            \
        }                                    
    #include "../utils/regs.hpp"
    #undef REG_DEF
    return false;
}

int IsCommand(Instruction& command, std::string cmd_name, int& arg_num)
{
    #define DEF_CMD(name, cpu_code, args_num, ...)       \
        if(cmd_name == #name)                             \
        {                                                  \
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
                                 ArgType arg_type)
{
    int arg_num = 0;
    if(!IsCommand(instr, cmd_name, arg_num))
    {
        return;
    }

    AppendInstrArgType(&(instr.cmd), arg_type); 
    //instructions[ass_file->cmd_num].cmd = instr.cmd;
    
    if(cmd_name == "POP" && arg_type == IMM)
    {
        //SetErrorBit(&ass_file->errors, ASM_POP_WITH_NUM);
        return;
    }

    if(arg_type != NOARG)
    {
        if(arg_num != 1) {
            return;
            //SetErrorBit(&ass_file->errors, ASM_TOO_FEW_ARGS);
        }
    }
    else if(arg_num != 0)
    {
        //SetErrorBit(&ass_file->errors, ASM_TOO_MANY_ARGS);
        return;
    }
    instructions.push_back(instr);
}

int AsmCompiler::ReadLine(std::istringstream& cur_str, 
                          Instruction& instr)
{
    std::string cmd_name;
    std::string str;

    cur_str >> cmd_name;
    if(cur_str >> str)
    {
        if(IsReg(instr, str))
        {
            //std::cout << str << "\n";
            SetInstruction(instr, cmd_name, REG);
        }
        else if(IsLabel(instr, str))
        {
            //std::cout << " " << str << "\n";
            SetInstruction(instr, cmd_name, LAB);
        }
        else
        {
            //std::cout << "чеее  " << str << "\n";
            instr.arg = std::stod(str);
            SetInstruction(instr, cmd_name, IMM);
        }
    }
    else
    {
        if(cmd_name[cmd_name.size() - 1] != ':')
        {
            instr.arg = 0;
            SetInstruction(instr, cmd_name, NOARG);
        }
    }
}

int AsmCompiler::ASMExecute(std::string wfile_name)
{
    Instruction command = {};

    std::ofstream file(wfile_name, std::ios::binary);
    
    int blank_lines_counter = 0;

    for(int line_num = 1; line_num < lines.size() + 1; ++line_num)
	{
        std::istringstream cur_str(lines[line_num - 1]);
        int cmd_size = lines[line_num - 1].size();
		std::string label_name;

        if(cur_str >> label_name )
        { 
            if(!(cur_str >> label_name)) {
                if(label_name[label_name.size() - 1] == ':')
                {
                    label_name.pop_back();
                    Label new_label(label_name, line_num - labels.size() - blank_lines_counter);
                    labels.push_back(new_label);
                }
            }
        }
        else
        {
            blank_lines_counter++;
        }
    }

    for(int line_num = 1; line_num <= lines.size(); ++line_num)
    {
        std::istringstream cur_str(lines[line_num - 1]);
        ReadLine(cur_str, command);
        Instruction command = {};
    }

    for(int i = 0; i < instructions.size(); ++i) {
        std::cout << instructions[i].cmd << " " << instructions[i].arg << "\n";
    }

    for(int i = 0; i < instructions.size(); ++i) {
        //Instruction cur_instr = instructions[i];
        file.write(reinterpret_cast<char*>(&instructions[i]), sizeof(Instruction));
    }
    file.close();
}

void AsmCompiler::ReadFile(std::ifstream& file)
{
    std::string line;
    while(std::getline(file, line)) {
        lines.push_back(line);
    }
}

AsmCompiler::AsmCompiler(std::string rfile_name) {
    std::ifstream file(rfile_name);
    ReadFile(file);
    file.close();

    instructions_num = 0;
}

