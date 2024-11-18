#ifndef ASM_H_
#define ASM_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "../utils/isa.hpp"
#include "../utils/label.hpp"

class AsmCompiler
{
public:
    std::vector<std::string> lines;
    std::vector<Label> labels;

    std::vector<Instruction> instructions;
    int instructions_num;

    AsmCompiler(std::string rfile_name);
    int ASMExecute(std::string wfile_name);
    void ReadFile(std::ifstream& file);
    int ReadLine(std::istringstream& cur_str, Instruction& instr);
    bool IsReg(Instruction& instr, std::string reg);
    bool IsLabel(Instruction& instr, std::string label);
    void SetInstruction(Instruction& instr, std::string cmd_name, ArgType arg_type);
};



#endif // #define ASM_H_