#include "VM.class.hpp"

int main(int argc, char **argv)
{
    VM avm;
    std::string file;

    if (argc > 1)
        file = argv[1];
    avm.start(file);
    return (0);
}