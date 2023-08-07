//
// Created by hartl on 20/07/2023.
//

#ifndef I8080EMULATOR_CPU_H
#define I8080EMULATOR_CPU_H
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "MMU/MMU.h"

// defining structures to represent the state of the system
// ConditionCodes: z = zero flag, s = sign flag, p = parity bit, cy and ac = carry flags
typedef struct ConditionCodes {
    uint8_t Zero:1;
    uint8_t Sign:1;
    uint8_t Parity:1;
    uint8_t Carry:1;
    uint8_t AuxiliaryCarry:1;
} ConditionCodes;

typedef struct Registers16Bit {
    uint16_t bc;
    uint16_t de;
    uint16_t hl;
} Registers16Bit;

// below is the struct for the state of the system - includes all registers
typedef struct State8080 {
    struct Registers16Bit regs{};
    uint8_t* b = ((uint8_t*) &regs.bc) + 1;
    uint8_t* c = ((uint8_t*) &regs.bc);
    uint8_t* d = ((uint8_t*) &regs.de) + 1;
    uint8_t* e = ((uint8_t*) &regs.de);
    uint8_t* h = ((uint8_t*) &regs.hl) + 1;
    uint8_t* l = ((uint8_t*) &regs.hl);
    uint16_t sp{};
    uint16_t pc{};
    struct ConditionCodes cc{};
} State8080;

class CPU {
public:
    explicit CPU(uint8_t ConsoleMode, MMU* _mmu);

    // I/O
    uint8_t InPort[4]{};
    uint8_t OutPort[7]{};

    // Status
    uint8_t InterruptsEnabled{};
    uint8_t Halt{};
    uint64_t ClockCount{};
    uint64_t InstructionCount{};
    uint8_t ConsoleMode{};
private:
    State8080 state;
    MMU* mmu;

    void Emulate8080();

    void LXI(uint8_t *Reg, uint16_t data);

    static uint8_t Parity(uint8_t byte);
    static uint16_t CombineChars(uint8_t a, uint8_t b);

    // used for debugging
    static int Disassemble8080Print(unsigned char *CodeBuffer, int pc);
};

#endif //I8080EMULATOR_CPU_H
