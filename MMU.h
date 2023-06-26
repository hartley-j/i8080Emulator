//
// Created by hartl on 25/06/2023.
//

#include <cstdint>
#include <cstring>

#ifndef I8080EMULATOR_MMU_H
#define I8080EMULATOR_MMU_H

// MMU Layout
/*
    ROM:			0x0000 - 0x1FFF
    RAM:			0x2000 - 0x23FF
    VRAM:			0x2400 - 0x3FFF
    RAMMirror:	0x4000 - 0x43FF
*/

class MMU {
public:
    explicit MMU(uint8_t ConsoleMode);

    // Addresses of different parts of memory
    uint16_t ROMAddress = 0x0000;
    uint16_t RAMAddress = 0x2000;
    uint16_t VRAMAddress = 0x2400;
    uint16_t RAMMirrorAddress = 0x4000;

    // Useful pointer to VRAM
    uint8_t* VRAM = memory + VRAMAddress;

    uint8_t* MemoryMap[0x10000]{}; // 64K
    void LoadInMemory(uint8_t* Buffer, uint16_t Address, int BufferSize);
    void testVRAMFlash(uint16_t height, uint16_t width);
private:
    uint8_t memory[0x10000]{};
};

#endif //I8080EMULATOR_MMU_H
