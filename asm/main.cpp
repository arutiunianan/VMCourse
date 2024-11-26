#include "asm.hpp"

int main(int argc, const char* argv[]) {
    if(argc == 3)
    {
        AsmCompiler ass{argv[1]};
        ass.Execute(argv[2]);
    }
    else
    {
        printf("Invalid number of args to program\n");
        return 1;
    }
    return 0;
}