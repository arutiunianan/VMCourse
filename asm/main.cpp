#include "asm.hpp"

int main() {
    AsmCompiler asmcom("../quadratic_equation.txt");
    asmcom.ASMExecute("../result.txt");
}