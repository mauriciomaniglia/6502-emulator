#include <iostream>

using Byte = unsigned char;
using Word = unsigned short;

struct CPU {
    Word PC;        // program counter
    Word SP;        // stack pointer

    Byte A;         // registers
    Byte X;
    Byte Y;

    Byte C : 1;     // status flags
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;
};

int main(int argc, const char * argv[]) {
    CPU cpu;
    return 0;
}
