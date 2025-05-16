#include <iostream>
#include "m6502.h"


int main(int argc, const char * argv[])
{
    Memory mem;
    CPU cpu;
    cpu.reset( mem );
    // start - inline a little program
    mem[0xFFFC] = CPU::INS_JSR;
    mem[0xFFFD] = 0x42;
    mem[0xFFFE] = 0x42;
    mem[0x4242] = CPU::INS_LDA_IM;
    mem[0x4243] = 0x84;
    // end - inline a little program
    cpu.execute(9, mem);
    return 0;
}
