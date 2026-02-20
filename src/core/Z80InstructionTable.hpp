#ifndef Z80_INSTRUCTION_TABLE_HPP_
#define Z80_INSTRUCTION_TABLE_HPP_
#include <cstdint>


/*
 * Ideas for organizing instructions via machine code:
 * 1. have each instruction byte size to be the complete size even those that are from other instruction tables.
 * 2. write a function that will recognize the first byte for other instruction tables.
 * 3. maybe store the entire instruction opcodes store in a vector.
 */

struct Z80Instruction {
    const char* mnemonic;
    uint8_t length;
};


/* Notation Table
 * 8-bit Registers: A, B, C, D, E, H, L (A', B', C', D' E', H', L')
 * Register Pairs: AF, BC, DE, HL (AF', BC', DE', HL')
 * 16-bit Registers: IX, IY, SP, PC
 * Special Registers: I, R
 * 1-byte unsigned integer: n
 * 2-byte unsigned integer: nn
 * Identify contents of a memory location: (BC), (DE), (HL), (nn)
 * 1-byte signed integer: e (-126 to +129)
 * Flags: C, N, P/V, H, Z, S
 * Conditions: Non-Zero(NZ), Non Carry(NC), Parity Odd(PO),
 * Parity Even(PE), Sign Positive(P), Sign Negative(M)
 */


static const Z80Instruction MAIN_INSTRUCTION_TABLE[256] = {
    /* 0x00 */
    {"NOP",1},        {"LD BC,nn",3}, {"LD (BC),A",1}, {"INC BC",1},
    {"INC B",1},      {"DEC B",1},     {"LD B,n",2},   {"RLCA",1},
    {"EX AF,AF'",1},  {"ADD HL,BC",1}, {"LD A,(BC)",1},{"DEC BC",1},
    {"INC C",1},      {"DEC C",1},     {"LD C,n",2},   {"RRCA",1},

    /* 0x10 */
    {"DJNZ d",2},     {"LD DE,nn",3},  {"LD (DE),A",1},{"INC DE",1},
    {"INC D",1},      {"DEC D",1},     {"LD D,n",2},   {"RLA",1},
    {"JR e",2},       {"ADD HL,DE",1}, {"LD A,(DE)",1},{"DEC DE",1},
    {"INC E",1},      {"DEC E",1},     {"LD E,n",2},   {"RRA",1},

    /* 0x20 */
    {"JR NZ,e",2},    {"LD HL,nn",3},  {"LD (nn),HL",3},{"INC HL",1},
    {"INC H",1},      {"DEC H",1},     {"LD H,n",2},   {"DAA",1},
    {"JR Z,e",2},     {"ADD HL,HL",1}, {"LD HL,(nn)",3},{"DEC HL",1},
    {"INC L",1},      {"DEC L",1},     {"LD L,n",2},   {"CPL",1},

    /* 0x30 */
    {"JR NC,e",2},    {"LD SP,nn",3},  {"LD (nn),A",3},{"INC SP",1},
    {"INC (HL)",1},   {"DEC (HL)",1},  {"LD (HL),n",2},{"SCF",1},
    {"JR C,e",2},     {"ADD HL,SP",1}, {"LD A,(nn)",3},{"DEC SP",1},
    {"INC A",1},      {"DEC A",1},     {"LD A,n",2},   {"CCF",1},

    /* 0x40 */
    {"LD B,B",1}, {"LD B,C",1}, {"LD B,D",1}, {"LD B,E",1},
    {"LD B,H",1}, {"LD B,L",1}, {"LD B,(HL)",1}, {"LD B,A",1},
    {"LD C,B",1}, {"LD C,C",1}, {"LD C,D",1}, {"LD C,E",1},
    {"LD C,H",1}, {"LD C,L",1}, {"LD C,(HL)",1}, {"LD C,A",1},

    /* 0x50 */
    {"LD D,B",1}, {"LD D,C",1}, {"LD D,D",1}, {"LD D,E",1},
    {"LD D,H",1}, {"LD D,L",1}, {"LD D,(HL)",1}, {"LD D,A",1},
    {"LD E,B",1}, {"LD E,C",1}, {"LD E,D",1}, {"LD E,E",1},
    {"LD E,H",1}, {"LD E,L",1}, {"LD E,(HL)",1}, {"LD E,A",1},

    /* 0x60 */
    {"LD H,B",1}, {"LD H,C",1}, {"LD H,D",1}, {"LD H,E",1},
    {"LD H,H",1}, {"LD H,L",1}, {"LD H,(HL)",1}, {"LD H,A",1},
    {"LD L,B",1}, {"LD L,C",1}, {"LD L,D",1}, {"LD L,E",1},
    {"LD L,H",1}, {"LD L,L",1}, {"LD L,(HL)",1}, {"LD L,A",1},

    /* 0x70 */
    {"LD (HL),B",1}, {"LD (HL),C",1}, {"LD (HL),D",1}, {"LD (HL),E",1},
    {"LD (HL),H",1}, {"LD (HL),L",1}, {"HALT",1},     {"LD (HL),A",1},
    {"LD A,B",1},    {"LD A,C",1},    {"LD A,D",1},    {"LD A,E",1},
    {"LD A,H",1},    {"LD A,L",1},    {"LD A,(HL)",1}, {"LD A,A",1},

    /* 0x80 */
    {"ADD A,B",1},{"ADD A,C",1},{"ADD A,D",1},{"ADD A,E",1},
    {"ADD A,H",1},{"ADD A,L",1},{"ADD A,(HL)",1},{"ADD A,A",1},
    {"ADC A,B",1},{"ADC A,C",1},{"ADC A,D",1},{"ADC A,E",1},
    {"ADC A,H",1},{"ADC A,L",1},{"ADC A,(HL)",1},{"ADC A,A",1},

    /* 0x90 */
    {"SUB B",1},{"SUB C",1},{"SUB D",1},{"SUB E",1},
    {"SUB H",1},{"SUB L",1},{"SUB (HL)",1},{"SUB A",1},
    {"SBC A,B",1},{"SBC A,C",1},{"SBC A,D",1},{"SBC A,E",1},
    {"SBC A,H",1},{"SBC A,L",1},{"SBC A,(HL)",1},{"SBC A,A",1},

    /* 0xA0 */
    {"AND B",1},{"AND C",1},{"AND D",1},{"AND E",1},
    {"AND H",1},{"AND L",1},{"AND (HL)",1},{"AND A",1},
    {"XOR B",1},{"XOR C",1},{"XOR D",1},{"XOR E",1},
    {"XOR H",1},{"XOR L",1},{"XOR (HL)",1},{"XOR A",1},

    /* 0xB0 */
    {"OR B",1},{"OR C",1},{"OR D",1},{"OR E",1},
    {"OR H",1},{"OR L",1},{"OR (HL)",1},{"OR A",1},
    {"CP B",1},{"CP C",1},{"CP D",1},{"CP E",1},
    {"CP H",1},{"CP L",1},{"CP (HL)",1},{"CP A",1},

    /* 0xC0 */
    {"RET NZ",1},{"POP BC",1},{"JP NZ,nn",3},{"JP nn",3},
    {"CALL NZ,nn",3},{"PUSH BC",1},{"ADD A,n",2},{"RST 00H",1},
    {"RET Z",1},{"RET",1},{"JP Z,nn",3},{"BIT TABLE",1},
    {"CALL Z,nn",3},{"CALL nn",3},{"ADC A,n",2},{"RST 08H",1},

    /* 0xD0 */
    {"RET NC",1},{"POP DE",1},{"JP NC,nn",3},{"OUT (n),A",2},
    {"CALL NC,nn",3},{"PUSH DE",1},{"SUB n",2},{"RST 10H",1},
    {"RET C",1},{"EXX",1},{"JP C,nn",3},{"IN A,(n)",2},
    {"CALL C,nn",3},{"IX TABLE",1},{"SBC A,n",2},{"RST 18H",1},

    /* 0xE0 */
    {"RET PO",1},{"POP HL",1},{"JP PO,nn",3},{"EX (SP),HL",1},
    {"CALL PO,nn",3},{"PUSH HL",1},{"AND n",2},{"RST 20H",1},
    {"RET PE",1},{"JP (HL)",1},{"JP PE,nn",3},{"EX DE,HL",1},
    {"CALL PE,nn",3},{"MISC TABLE",1},{"XOR n",2},{"RST 28H",1},

    /* 0xF0 */
    {"RET P",1},{"POP AF",1},{"JP P,nn",3},{"DI",1},
    {"CALL P,nn",3},{"PUSH AF",1},{"OR n",2},{"RST 30H",1},
    {"RET M",1},{"LD SP,HL",1},{"JP M,nn",3},{"EI",1},
    {"CALL M,nn",3},{"IY TABLE",1},{"CP n",2},{"RST 38H",1}
};


static const Z80Instruction MISC_INSTRUCTION_TABLE[256] = {
    /* 0x00 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x10 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x20 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x30 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x40 */
    {"IN B,(C)",1},{"OUT (C),B",1},{"SBC HL,BC",1},{"LD (nn),BC",3},
    {"NEG",1},{"RETN",1},{"IM 0",1},{"LD I,A",1},
    {"IN C,(C)",1},{"OUT (C),C",1},{"ADC HL,BC",1},{"LD BC,(nn)",3},
    {"NOP",1},{"RETI",1},{"NOP",1},{"LD R,A",1},

    /* 0x50 */
    {"IN D,(C)",1},{"OUT (C),D",1},{"SBC HL,DE",1},{"LD (nn),DE",3},
    {"NOP",1},{"NOP",1},{"IM 1",1},{"LD A,I",1},
    {"IN E,(C)",1},{"OUT (C),E",1},{"ADC HL,DE",1},{"LD DE,(nn)",3},
    {"NOP",1},{"NOP",1},{"IM 2",1},{"LD A,R",1},

    /* 0x60 */
    {"IN H,(C)",1},{"OUT (C),H",1},{"SBC HL,HL",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"RRD",1},
    {"IN L,(C)",1},{"OUT (C),L",1},{"ADC HL,HL",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"RLD",1},

    /* 0x70 */
    {"IN (C)",1},{"OUT (C),0",1},{"SBC HL,SP",1},{"LD (nn),SP",3},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"IN A,(C)",1},{"OUT (C),A",1},{"ADC HL,SP",1},{"LD SP,(nn)",3},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x80 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0x90 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xA0 */
    {"LDI",1},{"CPI",1},{"INI",1},{"OUTI",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"LDD",1},{"CPD",1},{"IND",1},{"OUTD",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xB0 */
    {"LDIR",1},{"CPIR",1},{"INIR",1},{"OTIR",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"LDDR",1},{"CPDR",1},{"INDR",1},{"OTDR",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xC0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xD0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xE0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xF0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
};


static const Z80Instruction IX_INSTRUCTION_TABLE[256] = {
    /* 0x00 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IX,BC",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x10 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IX,DE",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x20 */
    {"NOP",1},{"LD IX,nn",3},{"LD (nn),IX",3},{"INC IX",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IX,IX",1},{"LD IX,(nn)",3},{"DEC IX",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x30 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"INC (IX+d)",2},{"DEC (IX+d)",2},{"LD (IX+d),n",3},{"NOP",1},
    {"NOP",1},{"ADD IX,SP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x40 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD B,(IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD C, (IX+d)",2},{"NOP",1},

    /* 0x50 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD D,(IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD E, (IX+d)",2},{"NOP",1},

    /* 0x60 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD H,(IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD L, (IX+d)",2},{"NOP",1},

    /* 0x70 */
    {"LD (IX+d), B",2},{"LD (IX+d), C",2},{"LD (IX+d), D",2},{"LD (IX+d), E",2},
    {"LD (IX+d), H",2},{"LD (IX+d), L",2},{"NOP",1},{"LD (IX+d), A",2},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD A,(IX+d)",2},{"NOP",1},

    /* 0x80 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"ADD A,(IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"ADC A,(IX+d)",2},{"NOP",1},

    /* 0x90 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"SUB(IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"SBC A,(IX+d)",2},{"NOP",1},

    /* 0xA0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"AND (IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"XOR (IX+d)",2},{"NOP",1},

    /* 0xB0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"OR (IX+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"CP (IX+d)",2},{"NOP",1},

    /* 0xC0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"IX BIT TABLE",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xD0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0xE0 */
    {"NOP",1},{"POP IX",1},{"NOP",1},{"EX (SP),IX",1},
    {"NOP",1},{"PUSH IX",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"JP (IX)",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0xF0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"LD SP,IX",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1}
};


static const Z80Instruction IY_INSTRUCTION_TABLE[256] = {
    /* 0x00 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IY,BC",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x10 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IY,DE",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x20 */
    {"NOP",1},{"LD IY,nn",3},{"LD (nn),IY",3},{"INC IY",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"ADD IY,IY",1},{"LD IY,(nn)",3},{"DEC IY",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x30 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"INC (IY+d)",2},{"DEC (IY+d)",2},{"LD (IY+d),n",3},{"NOP",1},
    {"NOP",1},{"ADD IY,SP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0x40 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD B,(IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD C, (IY+d)",2},{"NOP",1},

    /* 0x50 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD D,(IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD E, (IY+d)",2},{"NOP",1},

    /* 0x60 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD H,(IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD L, (IY+d)",2},{"NOP",1},

    /* 0x70 */
    {"LD (IY+d), B",2},{"LD (IY+d), C",2},{"LD (IY+d), D",2},{"LD (IY+d), E",2},
    {"LD (IY+d), H",2},{"LD (IY+d), L",2},{"NOP",1},{"LD (IY+d), A",2},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"LD A,(IY+d)",2},{"NOP",1},

    /* 0x80 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"ADD A,(IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"ADC A,(IY+d)",2},{"NOP",1},

    /* 0x90 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"SUB(IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"SBC A,(IY+d)",2},{"NOP",1},

    /* 0xA0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"AND (IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"XOR (IY+d)",2},{"NOP",1},

    /* 0xB0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"OR (IY+d)",2},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"CP (IY+d)",2},{"NOP",1},

    /* 0xC0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"IY BIT TABLE",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    /* 0xD0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0xE0 */
    {"NOP",1},{"POP IY",1},{"NOP",1},{"EX (SP),IY",1},
    {"NOP",1},{"PUSH IY",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"JP (IY)",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},

    /* 0xF0 */
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"LD SP,IY",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1}
};


static const Z80Instruction BIT_INSTRUCTION_TABLE[256] = {
    // 0x00
    {"RLC B",2},{"RLC C",2},{"RLC D",2},{"RLC E",2},
    {"RLC H",2},{"RLC L",2},{"RLC (HL)",2},{"RLC A",2},
    {"RRC B",2},{"RRC C",2},{"RRC D",2},{"RRC E",2},
    {"RRC H",2},{"RRC L",2},{"RRC (HL)",2},{"RRC A",2},

    // 0x10
    {"RL B",2},{"RL C",2},{"RL D",2},{"RL E",2},
    {"RL H",2},{"RL L",2},{"RL (HL)",2},{"RL A",2},
    {"RR B",2},{"RR C",2},{"RR D",2},{"RR E",2},
    {"RR H",2},{"RR L",2},{"RR (HL)",2},{"RR A",2},

    // 0x20
    {"SLA B",2},{"SLA C",2},{"SLA D",2},{"SLA E",2},
    {"SLA H",2},{"SLA L",2},{"SLA (HL)",2},{"SLA A",2},
    {"SRA B",2},{"SRA C",2},{"SRA D",2},{"SRA E",2},
    {"SRA H",2},{"SRA L",2},{"SRA (HL)",2},{"SRA A",2},

    // 0x30
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"NOP",1},{"NOP",1},{"NOP",1},{"NOP",1},
    {"SRL B",2},{"SRL C",2},{"SRL D",2},{"SRL E",2},
    {"SRL H",2},{"SRL L",2},{"SRL (HL)",2},{"SRL A",2},

    // 0x40
    {"BIT 0,B",2},{"BIT 0,C",2},{"BIT 0,D",2},{"BIT 0,E",2},
    {"BIT 0,H",2},{"BIT 0,L",2},{"BIT 0,(HL)",2},{"BIT 0,A",2},
    {"BIT 1,B",2},{"BIT 1,C",2},{"BIT 1,D",2},{"BIT 1,E",2},
    {"BIT 1,H",2},{"BIT 1,L",2},{"BIT 1,(HL)",2},{"BIT 1,A",2},

    // 0x50
    {"BIT 2,B",2},{"BIT 2,C",2},{"BIT 2,D",2},{"BIT 2,E",2},
    {"BIT 2,H",2},{"BIT 2,L",2},{"BIT 2,(HL)",2},{"BIT 2,A",2},
    {"BIT 3,B",2},{"BIT 3,C",2},{"BIT 3,D",2},{"BIT 3,E",2},
    {"BIT 3,H",2},{"BIT 3,L",2},{"BIT 3,(HL)",2},{"BIT 3,A",2},

    // 0x60
    {"BIT 4,B",2},{"BIT 4,C",2},{"BIT 4,D",2},{"BIT 4,E",2},
    {"BIT 4,H",2},{"BIT 4,L",2},{"BIT 4,(HL)",2},{"BIT 4,A",2},
    {"BIT 5,B",2},{"BIT 5,C",2},{"BIT 5,D",2},{"BIT 5,E",2},
    {"BIT 5,H",2},{"BIT 5,L",2},{"BIT 5,(HL)",2},{"BIT 5,A",2},

    // 0x70
    {"BIT 6,B",2},{"BIT 6,C",2},{"BIT 6,D",2},{"BIT 6,E",2},
    {"BIT 6,H",2},{"BIT 6,L",2},{"BIT 6,(HL)",2},{"BIT 6,A",2},
    {"BIT 7,B",2},{"BIT 7,C",2},{"BIT 7,D",2},{"BIT 7,E",2},
    {"BIT 7,H",2},{"BIT 7,L",2},{"BIT 7,(HL)",2},{"BIT 7,A",2},

    // 0x80
    {"RES 0,B",2},{"RES 0,C",2},{"RES 0,D",2},{"RES 0,E",2},
    {"RES 0,H",2},{"RES 0,L",2},{"RES 0,(HL)",2},{"RES 0,A",2},
    {"RES 1,B",2},{"RES 1,C",2},{"RES 1,D",2},{"RES 1,E",2},
    {"RES 1,H",2},{"RES 1,L",2},{"RES 1,(HL)",2},{"RES 1,A",2},

    // 0x90
    {"RES 2,B",2},{"RES 2,C",2},{"RES 2,D",2},{"RES 2,E",2},
    {"RES 2,H",2},{"RES 2,L",2},{"RES 2,(HL)",2},{"RES 2,A",2},
    {"RES 3,B",2},{"RES 3,C",2},{"RES 3,D",2},{"RES 3,E",2},
    {"RES 3,H",2},{"RES 3,L",2},{"RES 3,(HL)",2},{"RES 3,A",2},

    // 0xA0
    {"RES 4,B",2},{"RES 4,C",2},{"RES 4,D",2},{"RES 4,E",2},
    {"RES 4,H",2},{"RES 4,L",2},{"RES 4,(HL)",2},{"RES 4,A",2},
    {"RES 5,B",2},{"RES 5,C",2},{"RES 5,D",2},{"RES 5,E",2},
    {"RES 5,H",2},{"RES 5,L",2},{"RES 5,(HL)",2},{"RES 5,A",2},

    // 0xB0
    {"RES 6,B",2},{"RES 6,C",2},{"RES 6,D",2},{"RES 6,E",2},
    {"RES 6,H",2},{"RES 6,L",2},{"RES 6,(HL)",2},{"RES 6,A",2},
    {"RES 7,B",2},{"RES 7,C",2},{"RES 7,D",2},{"RES 7,E",2},
    {"RES 7,H",2},{"RES 7,L",2},{"RES 7,(HL)",2},{"RES 7,A",2},

    // 0xC0
    {"SET 0,B",2},{"SET 0,C",2},{"SET 0,D",2},{"SET 0,E",2},
    {"SET 0,H",2},{"SET 0,L",2},{"SET 0,(HL)",2},{"SET 0,A",2},
    {"SET 1,B",2},{"SET 1,C",2},{"SET 1,D",2},{"SET 1,E",2},
    {"SET 1,H",2},{"SET 1,L",2},{"SET 1,(HL)",2},{"SET 1,A",2},

    // 0xD0
    {"SET 2,B",2},{"SET 2,C",2},{"SET 2,D",2},{"SET 2,E",2},
    {"SET 2,H",2},{"SET 2,L",2},{"SET 2,(HL)",2},{"SET 2,A",2},
    {"SET 3,B",2},{"SET 3,C",2},{"SET 3,D",2},{"SET 3,E",2},
    {"SET 3,H",2},{"SET 3,L",2},{"SET 3,(HL)",2},{"SET 3,A",2},

    // 0xE0
    {"SET 4,B",2},{"SET 4,C",2},{"SET 4,D",2},{"SET 4,E",2},
    {"SET 4,H",2},{"SET 4,L",2},{"SET 4,(HL)",2},{"SET 4,A",2},
    {"SET 5,B",2},{"SET 5,C",2},{"SET 5,D",2},{"SET 5,E",2},
    {"SET 5,H",2},{"SET 5,L",2},{"SET 5,(HL)",2},{"SET 5,A",2},

    // 0xF0
    {"SET 6,B",2},{"SET 6,C",2},{"SET 6,D",2},{"SET 6,E",2},
    {"SET 6,H",2},{"SET 6,L",2},{"SET 6,(HL)",2},{"SET 6,A",2},
    {"SET 7,B",2},{"SET 7,C",2},{"SET 7,D",2},{"SET 7,E",2},
    {"SET 7,H",2},{"SET 7,L",2},{"SET 7,(HL)",2},{"SET 7,A",2}
};




#endif
