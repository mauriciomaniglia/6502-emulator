#include <iostream>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory {
    static constexpr u32 MAX_MEM = 1024 * 64;

    Byte Data[MAX_MEM];

    void Initialize() {
        for (u32 i =0; i < MAX_MEM; i++) {
            Data[i] = 0;
        }
    }

    // read 1 byte
    Byte operator[](u32 address) const {
        return Data[address];
    }
};

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

    void Reset(Memory& memory) {
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

        memory.Initialize();
    }

    Byte FetchByte(u32& cycles, Memory& memory) {
        Byte Data = memory[PC];
        PC++;

        return Data;
    }

    void Execute(u32 cycles, Memory& memory) {
        while (cycles > 0) {
            Byte Instruction = FetchByte(cycles, memory);
        }
    }
};

int main(int argc, const char * argv[]) {
    Memory memory;
    CPU cpu;
    cpu.Reset(memory);
    cpu.Execute(2, memory);
    return 0;
}
