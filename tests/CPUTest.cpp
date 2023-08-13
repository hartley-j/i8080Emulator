//
// Created by joehartley on 07/08/23.
//

#include <gtest/gtest.h>
#include "CPU/CPU.h"
#include "MMU/MMU.h"

class CPUTest : public ::testing::Test {};

// Helper function to emulate the next step of the program
// and output the current processor state.
State8080 EmulateThenDump(CPU* cpu, int cycles);

TEST_F(CPUTest, TestLXI) {
    MMU memory = MMU(1);
    uint8_t testBuffer[12] = {0x01, 0xFF, 0xFF,
                               0x11, 0xFF, 0xFF,
                               0x21, 0xFF, 0xFF,
                               0x31, 0xFF, 0xFF};
    memory.LoadInMemory(testBuffer,
                        0x0000,
                        sizeof(testBuffer));

    State8080 DumpState;
    State8080 TestState;
    TestState.pc = 0x0000;

    CPU TestEmulator = CPU(1, &memory);
    TestEmulator.SetStates(TestState);

    // Emulate all LXI instructions:
    DumpState = EmulateThenDump(&TestEmulator, 3);

    ASSERT_EQ(DumpState.bc, 0xFFFF);
    EXPECT_EQ(DumpState.de, 0xFFFF);
    EXPECT_EQ(DumpState.hl, 0xFFFF);
    EXPECT_EQ(DumpState.sp, 0xFFFF);
}

TEST_F(CPUTest, TestMOV) {
    MMU Memory = MMU(1);
    uint8_t TestBuffer[10] = {0x56, 0x5E, 0x66,
                              0x66,0x6F, 0x77,
                              0x7A, 0x7B, 0x7C,
                              0x7E};
    uint8_t TestData[1] = {0x6A};

    Memory.LoadInMemory(TestBuffer,
                        0x0000,
                        sizeof(TestBuffer));
    Memory.LoadInMemory(TestData,
                        Memory.RAMAddress,
                        sizeof(TestData));

    ASSERT_EQ(*Memory.MemoryMap[Memory.RAMAddress], 0x6A);

    State8080 DumpState;
    State8080 TestState;
    TestState.pc = 0x0000;
    *TestState.a = 0xFA;
    // TestState.de = 0xFFAA;
    TestState.hl = Memory.RAMAddress;

    CPU TestEmulator = CPU(1, &Memory);
    TestEmulator.SetStates(TestState);

    DumpState = EmulateThenDump(&TestEmulator, 10);

    ASSERT_EQ(*DumpState.d, 0x6A);
    EXPECT_EQ(*DumpState.e, 0x6A);
    EXPECT_EQ(*DumpState.h, 0x6A);
    EXPECT_EQ(*DumpState.l, 0xFA);
    EXPECT_EQ(*Memory.MemoryMap[Memory.RAMAddress], 0xFA);
}

State8080 EmulateThenDump(CPU* cpu, int cycles) {
    for (int i = 0; i <= cycles; i++) {
        cpu->Emulate8080();
    }
    return cpu->DumpState();
}