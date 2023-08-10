//
// Created by joehartley on 07/08/23.
//

#include <gtest/gtest.h>
#include "CPU/CPU.h"
#include "MMU/MMU.h"

class CPUTest : public ::testing::Test {};

TEST_F(CPUTest, TestLXI) {
    MMU memory = MMU(1);
    uint8_t testBuffer[12] = {0x01, 0xFF, 0xFF,
                               0x11, 0xFF, 0xFF,
                               0x21, 0xFF, 0xFF,
                               0x31, 0xFF, 0xFF};
    memory.loadInMemory(testBuffer,
                        0x0000,
                        sizeof(testBuffer));

    State8080 DumpState;
    State8080 TestState;
    TestState.pc = 0x0000;

    CPU TestEmulator = CPU(1, &memory);
    TestEmulator.SetStates(TestState);

    // Emulate all LXI instructions:
    for (int i=0; i<=3; i++) {
        TestEmulator.Emulate8080();
    }
    DumpState = TestEmulator.DumpState();


    ASSERT_EQ(DumpState.bc, 0xFFFF);
    EXPECT_EQ(DumpState.de, 0xFFFF);
    EXPECT_EQ(DumpState.hl, 0xFFFF);
    EXPECT_EQ(DumpState.sp, 0xFFFF);
}