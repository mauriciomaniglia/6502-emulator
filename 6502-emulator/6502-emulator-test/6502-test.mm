#import <XCTest/XCTest.h>
#include "m6502.h"

@interface _502_emulator_test : XCTestCase

@end

@implementation _502_emulator_test

Memory memory;
CPU cpu;

- (void)setUp {
    // Put setup code here. This method is called before the invocation of each test method in the class.
    cpu.reset(memory);
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
}

- (void)test_m6502_runALittleInlineProgram {
    memory[0xFFFC] = CPU::INS_JSR;
    memory[0xFFFD] = 0x42;
    memory[0xFFFE] = 0x42;
    memory[0x4242] = CPU::INS_LDA_IM;
    memory[0x4243] = 0x84;

    // Execute 9 cycles
    cpu.execute(9, memory);

    // Assertions
    XCTAssertEqual(cpu.A, 0x84, @"A register should contain 0x84 after LDA_IM");
}

@end
