#include "Z80Disassembler.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <cstring>   // for std::strcmp
#include "Z80InstructionTable.hpp"


std::vector<uint8_t> loadRomFile(const std::string& rom_path) {
    std::ifstream rom_file(rom_path, std::ios::binary | std::ios::ate);
    if (!rom_file) {
        std::cerr << "Failed to open ROM file: " << rom_path << "\n";
        return {};
    }

    // Get size
    std::streamsize size = rom_file.tellg();
    rom_file.seekg(0, std::ios::beg);

    // Allocate vector
    std::vector<uint8_t> buffer(size);

    // Read data
    if (!rom_file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        std::cerr << "Failed to read ROM file: " << rom_path << "\n";
        return {};
    }

    std::cout << "Loaded ROM: " << rom_path << " (" << size << " bytes)\n";
    return buffer;
}


void disassembleZ80(const std::vector<uint8_t>& code,
                    const std::filesystem::path& output_asm)
{
    std::ofstream out(output_asm);

    if (!out) {
        std::cerr << "Failed to create asm file\n";
        return;
    }

    uint16_t pc = 0x0000;
    size_t i = 0;

    while (i < code.size()) {

        uint8_t opcode = code[i];
        const Z80Instruction* inst = nullptr;
        size_t prefix_bytes = 0;

        const Z80Instruction& mainInst = MAIN_INSTRUCTION_TABLE[opcode];

        // ----- PREFIX CHECK -----

        if (opcode == 0xCB &&
            std::strcmp(mainInst.mnemonic, "BIT TABLE") == 0)
        {
            if (i + 1 >= code.size()) break;

            uint8_t next = code[i + 1];
            inst = &BIT_INSTRUCTION_TABLE[next];
            prefix_bytes = 1;
        }
        else if (opcode == 0xDD &&
                 std::strcmp(mainInst.mnemonic, "IX TABLE") == 0)
        {
            if (i + 1 >= code.size()) break;

            uint8_t next = code[i + 1];
            inst = &IX_INSTRUCTION_TABLE[next];
            prefix_bytes = 1;
        }
        else if (opcode == 0xED &&
                 std::strcmp(mainInst.mnemonic, "MISC TABLE") == 0)
        {
            if (i + 1 >= code.size()) break;

            uint8_t next = code[i + 1];
            inst = &MISC_INSTRUCTION_TABLE[next];
            prefix_bytes = 1;
        }
        else if (opcode == 0xFD &&
                 std::strcmp(mainInst.mnemonic, "IY TABLE") == 0)
        {
            if (i + 1 >= code.size()) break;

            uint8_t next = code[i + 1];
            inst = &IY_INSTRUCTION_TABLE[next];
            prefix_bytes = 1;
        }
        else
        {
            inst = &mainInst;
        }

        if (!inst) break;

        // ----- PRINT ADDRESS -----
        out << std::hex << std::setw(4) << std::setfill('0')
            << pc << ": ";

        // ----- PRINT MNEMONIC -----
        out << inst->mnemonic;

        size_t total_length = inst->length + prefix_bytes;

        // ----- HANDLE IMMEDIATES -----
        if (inst->length == 2) {
            uint8_t imm = code[i + 1 + prefix_bytes];
            out << " #" << std::setw(2) << (int)imm;
        }
        else if (inst->length == 3) {
            uint16_t imm =
                code[i + 1 + prefix_bytes] |
                (code[i + 2 + prefix_bytes] << 8);
            out << " #" << std::setw(4) << imm;
        }

        out << "\n";

        i += total_length;
        pc += total_length;
    }

    std::cout << "Disassembly written to " << output_asm << "\n";
}
