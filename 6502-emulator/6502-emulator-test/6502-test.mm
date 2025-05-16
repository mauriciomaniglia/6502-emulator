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

- (void)test_LDAImmediate_canLoadAValueIntoTheARegister {
    // Given
    memory[0xFFFC] = CPU::INS_LDA_IM;
    memory[0xFFFD] = 0x84;

    // When
    cpu.execute(2, memory);

    // Then
    XCTAssertEqual(cpu.A, 0x84);
}

@end
