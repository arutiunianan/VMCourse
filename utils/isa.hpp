#ifndef ISA_H_
#define ISA_H_

#include "stack.hpp"

enum Regs  {
    #define REG_DEF(name, reg_code) name = reg_code,

    #include "regs.hpp"
    #undef REG_DEF
};

enum ArgType {
    NOARG = 0,
    IMM   = 1 << 5, 
    REG   = 1 << 6,
    LAB   = 1 << 7,
};

enum Cmds  {
    #define DEF_CMD(name, cpu_code, ...) name = cpu_code,

    #include "cmds.hpp"
    #undef DEF_CMD
};

class Instruction {
public:
    Cmds cmd;
    Elem_t arg;
};

#endif // #define ISA_H_