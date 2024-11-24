#ifndef CPU_H_
#define CPU_H_

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>

#include "../utils/isa.hpp"
#include "../utils/label.hpp"

class Registers {
public:
    #define REG_DEF(name, ...) Elem_t name;

    #include "../utils/regs.hpp"
    #undef REG_DEF

};

/*class Frame {
    Stack stack;
    Frame* pframe;

    Frame(Frame* mamaframe): pframe(mamaframe) {}
};*/

class Core {
public:
    Core(std::string file_name);
    int Execute();

private:
    void ReadFile(std::ifstream& file);
    void SetReg(Elem_t reg, Elem_t value);
    Elem_t GetValidArgument(ArgType arg_type, Instruction& istr);

public:
    Stack stack;

    Registers registers;

    int current_line;
    std::vector<Instruction> instructions;
};

#endif // #define CPU_H_