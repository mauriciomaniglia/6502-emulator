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
    CPU cpuCopy = cpu;
    cpu.execute(2, memory);

    // Then
    XCTAssertEqual(cpu.A, 0x84);
    XCTAssertFalse(cpu.Z);
    XCTAssertTrue(cpu.N);
    XCTAssertEqual(cpu.C, cpuCopy.C);
    XCTAssertEqual(cpu.I, cpuCopy.I);
    XCTAssertEqual(cpu.D, cpuCopy.D);
    XCTAssertEqual(cpu.B, cpuCopy.B);
    XCTAssertEqual(cpu.V, cpuCopy.V);
}

- (void)test_LDAZeroPage_canLoadAValueIntoTheARegister {
    // Given
    memory[0xFFFC] = CPU::INS_LDA_ZP;
    memory[0xFFFD] = 0x42;
    memory[0x0042] = 0x37;

    // When
    CPU cpuCopy = cpu;
    cpu.execute(3, memory);

    // Then
    XCTAssertEqual(cpu.A, 0x37);
    XCTAssertFalse(cpu.Z);
    XCTAssertFalse(cpu.N);
    XCTAssertEqual(cpu.C, cpuCopy.C);
    XCTAssertEqual(cpu.I, cpuCopy.I);
    XCTAssertEqual(cpu.D, cpuCopy.D);
    XCTAssertEqual(cpu.B, cpuCopy.B);
    XCTAssertEqual(cpu.V, cpuCopy.V);
}

- (void)test_LDAZeroPageX_canLoadAValueIntoTheARegister {
    // Given
    cpu.X = 5;
    memory[0xFFFC] = CPU::INS_LDA_ZPX;
    memory[0xFFFD] = 0x42;
    memory[0x0047] = 0x37;

    // When
    CPU cpuCopy = cpu;
    cpu.execute(4, memory);

    // Then
    XCTAssertEqual(cpu.A, 0x37);
    XCTAssertFalse(cpu.Z);
    XCTAssertFalse(cpu.N);
    XCTAssertEqual(cpu.C, cpuCopy.C);
    XCTAssertEqual(cpu.I, cpuCopy.I);
    XCTAssertEqual(cpu.D, cpuCopy.D);
    XCTAssertEqual(cpu.B, cpuCopy.B);
    XCTAssertEqual(cpu.V, cpuCopy.V);
}

- (void)test_LDAZeroPageX_canLoadAValueIntoTheARegisterWhenItWraps {
    // Given
    cpu.X = 0xFF;
    memory[0xFFFC] = CPU::INS_LDA_ZPX;
    memory[0xFFFD] = 0x80;
    memory[0x007F] = 0x37;

    // When
    CPU cpuCopy = cpu;
    cpu.execute(4, memory);

    // Then
    XCTAssertEqual(cpu.A, 0x37);
    XCTAssertFalse(cpu.Z);
    XCTAssertFalse(cpu.N);
    XCTAssertEqual(cpu.C, cpuCopy.C);
    XCTAssertEqual(cpu.I, cpuCopy.I);
    XCTAssertEqual(cpu.D, cpuCopy.D);
    XCTAssertEqual(cpu.B, cpuCopy.B);
    XCTAssertEqual(cpu.V, cpuCopy.V);
}

@end
