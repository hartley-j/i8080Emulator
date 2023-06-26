//
// Created by hartl on 25/06/2023.
//

#include "MMU.h"

MMU::MMU(uint8_t ConsoleMode) {
    memset (memory, 0, sizeof(memory));
    memset(VRAM, 0, RAMMirrorAddress - VRAMAddress);

    for (int i = 0x0000; i < 0x4000; i++) { // ROM + RAM + VRAM
        MemoryMap[i] = memory + i;
    }

    if (!ConsoleMode) {
        for (int i = 0x4000; i < 0x4400; i++) // Mirrored RAM
            MemoryMap[i] = memory + i - 0x2000;
    } else {
        for (int i = 0x4000; i <= 0xFFFF; i++) // Unmirrored
            MemoryMap[i] = memory + i;
    }
}

void MMU::LoadInMemory(uint8_t *Buffer, uint16_t Address, int BufferSize) {
    for (int i = 0; i < BufferSize; i++)
        *(MemoryMap[Address + i]) = Buffer[i];
}

void MMU::testVRAMFlash(uint16_t height, uint16_t width) {
    uint8_t ColorToDraw = 0x00;

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            uint8_t VRAMByte = VRAM[x * (height >> 3) + (y >> 3)];

            ColorToDraw = VRAMByte ^ 0xff;
            VRAM[x * (height >> 3) + (y >> 3)] = ColorToDraw;
        }
    }
}
