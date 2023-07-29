//
// Created by hartl on 25/06/2023.
//

#include "MMU/MMU.h"

MMU::MMU(uint8_t ConsoleMode) {
    memset(memory, 0, sizeof(memory));
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

void MMU::loadInMemory(uint8_t *Buffer, uint16_t Address, int BufferSize) {
    for (int i = 0; i < BufferSize; i++)
        *(MemoryMap[Address + i]) = Buffer[i];
}
