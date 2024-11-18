#ifndef ASM_H_
#define ASM_H_

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>
#include <fstream>

#include "../utils/isa.hpp"
#include "../utils/label.hpp"

class AsmCompiler {
private:
    std::vector<std::string> lines;
    std::vector<Label>       labels;
    std::vector<Instruction> instructions;

public:
    AsmCompiler(std::string rfile_name);

    void Execute(std::string wfile_name);

private:
    void ReadFile(std::ifstream& file);
    void ReadLine(std::istringstream& cur_str, Instruction& instr);
    
    bool IsReg  (Instruction& instr, std::string reg);
    bool IsLabel(Instruction& instr, std::string label);

    void SetInstruction(Instruction& instr, std::string cmd_name, ArgType arg_type);
};



#endif // #define ASM_H_