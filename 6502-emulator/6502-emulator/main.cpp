#include <iostream>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory
{
    static constexpr u32 MAX_MEM = 1024 * 64;

    Byte data[MAX_MEM];

    void initialize()
    {
        for (u32 i =0; i < MAX_MEM; i++) {
            data[i] = 0;
        }
    }

    // read 1 byte
    Byte operator[](u32 address) const
    {
        return data[address];
    }

    // write 2 bytes
    void writeWord(Word value, u32 address, u32& cycles)
    {
        data[address]       = value & 0xFF;
        data[address+1]     = (value >> 8);
        cycles -= 2;
    }
};

struct CPU
{
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

    void reset(Memory& memory)
    {
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

        memory.initialize();
    }

    Byte fetchByte(u32& cycles, Memory& memory)
    {
        Byte data = memory[PC];
        PC++;
        cycles--;
        return data;
    }

    Byte fetchWord(u32& cycles, Memory& memory)
    {
        // 6502 is little endia
        Word data = memory[PC];
        PC++;

        data |= (memory[PC] << 8);
        PC++;

        cycles += 2;

        return data;
    }

    Byte readByte(u32& cycles, Byte address, Memory& memory)
    {
        Byte data = memory[address];
        cycles--;
        return data;
    }

    void LDASetStatus()
    {
        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }

    // opcodes
    static constexpr Byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5,
        INS_LDA_ZPX = 0xB5,
        INS_JSR = 0x20;

    void execute(u32 cycles, Memory& memory)
    {
        while (cycles > 0)
        {
            Byte ins = fetchByte(cycles, memory);

            switch (ins)
            {
                case INS_LDA_IM:
                {
                    Byte value = fetchByte(cycles, memory);
                    A = value;
                    LDASetStatus();
                } break;
                case INS_LDA_ZP:
                {
                    Byte zeroPageAddress = fetchByte(cycles, memory);
                    A = readByte(cycles, zeroPageAddress, memory);
                    LDASetStatus();
                } break;
                case INS_LDA_ZPX:
                {
                    Byte zeroPageAddress = fetchByte(cycles, memory);
                    zeroPageAddress += X;
                    cycles--;
                    A = readByte(cycles, zeroPageAddress, memory);
                    LDASetStatus();
                } break;
                case INS_JSR:
                {
                    Word subAddr = fetchWord(cycles, memory);
                    memory.writeWord(PC - 1, SP, cycles);
                    PC = subAddr;
                    cycles--;
                }
                default:
                {
                    printf("Instruction not handled %d", ins);
                } break;
            }
        }
    }
};

int main(int argc, const char * argv[])
{
    Memory memory;
    CPU cpu;
    cpu.reset(memory);
    cpu.execute(2, memory);
    return 0;
}
