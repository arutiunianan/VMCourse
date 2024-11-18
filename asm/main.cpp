#include "asm.hpp"

int main() {
    AsmCompiler asmcom("../test/quadratic_equation.txt");
    asmcom.Execute("../test/binary.txt");
}