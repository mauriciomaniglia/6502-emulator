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

    void Reset() {
        PC = 0xFFFC;
        SP = 0x0100;

        D = 0;
        A = 0;
        X = 0;
        Y = 0;

        C = 0;
        Z = 0;
        I = 0;
        D = 0;
        B = 0;
        V = 0;
        N = 0;
    }
};

int main(int argc, const char * argv[]) {
    CPU cpu;
    cpu.Reset()
    return 0;
}
