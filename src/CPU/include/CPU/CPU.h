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

// below is the struct for the state of the system - includes all registers
typedef struct State8080 {
    uint16_t bc{};
    uint16_t de{};
    uint16_t hl{};
    uint16_t a_real{};
    uint8_t* a = ((uint8_t*) &a_real) + 1;
    uint8_t* b = ((uint8_t*) &bc) + 1;
    uint8_t* c = ((uint8_t*) &bc);
    uint8_t* d = ((uint8_t*) &de) + 1;
    uint8_t* e = ((uint8_t*) &de);
    uint8_t* h = ((uint8_t*) &hl) + 1;
    uint8_t* l = ((uint8_t*) &hl);
    uint16_t sp{};
    uint16_t pc{};
    struct ConditionCodes cc{};
} State8080;

class CPU {
public:
    explicit CPU(uint8_t ConsoleMode, MMU* _mmu);

    void Emulate8080();

    // I/O
    uint8_t InPort[4]{};
    uint8_t OutPort[7]{};

    // Status
    uint8_t InterruptsEnabled{};
    uint8_t Halt{};
    uint64_t ClockCount{};
    uint64_t InstructionCount{};
    uint8_t ConsoleMode{};

    // Testing methods
    void PrintState() const;
    State8080 DumpState();
    void SetStates(State8080 set);
private:
    State8080 state;
    MMU* mmu;

    static void LXI(uint16_t *Reg, uint8_t Byte1, uint8_t Byte2);
    static void MOV(uint8_t *Reg1, const uint8_t *Reg2);
    static void DCR(uint8_t *Reg);

    static uint8_t Parity(uint8_t byte);
    static uint16_t CombineChars(uint8_t a, uint8_t b);

    // used for debugging
    static int Disassemble8080Print(unsigned char *CodeBuffer, int pc);
};

#endif //I8080EMULATOR_CPU_H
