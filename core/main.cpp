#include "core.hpp"

int main(int argc, const char* argv[])
{
    if(argc == 2)
    {
        Core core{argv[1]};
        core.Execute();
    }
    else
    {
        printf("Invalid number of args to program\n");
        return 1;
    }
    return 0;
}