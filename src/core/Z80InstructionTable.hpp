#ifndef Z80_INSTRUCTION_TABLE_HPP_
#define Z80_INSTRUCTION_TABLE_HPP_
#include <cstdint>

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


Z80Instruction main_instruction_table[256] = {
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
    {"RET Z",1},{"RET",1},{"JP Z,nn",3},{"CB",1},
    {"CALL Z,nn",3},{"CALL nn",3},{"ADC A,n",2},{"RST 08H",1},

    /* 0xD0 */
    {"RET NC",1},{"POP DE",1},{"JP NC,nn",3},{"OUT (n),A",2},
    {"CALL NC,nn",3},{"PUSH DE",1},{"SUB n",2},{"RST 10H",1},
    {"RET C",1},{"EXX",1},{"JP C,nn",3},{"IN A,(n)",2},
    {"CALL C,nn",3},{"DD",1},{"SBC A,n",2},{"RST 18H",1},

    /* 0xE0 */
    {"RET PO",1},{"POP HL",1},{"JP PO,nn",3},{"EX (SP),HL",1},
    {"CALL PO,nn",3},{"PUSH HL",1},{"AND n",2},{"RST 20H",1},
    {"RET PE",1},{"JP (HL)",1},{"JP PE,nn",3},{"EX DE,HL",1},
    {"CALL PE,nn",3},{"ED",1},{"XOR n",2},{"RST 28H",1},

    /* 0xF0 */
    {"RET P",1},{"POP AF",1},{"JP P,nn",3},{"DI",1},
    {"CALL P,nn",3},{"PUSH AF",1},{"OR n",2},{"RST 30H",1},
    {"RET M",1},{"LD SP,HL",1},{"JP M,nn",3},{"EI",1},
    {"CALL M,nn",3},{"FD",1},{"CP n",2},{"RST 38H",1}
};


#endif
