#include "Z80Disassembler.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>
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


void disassembleZ80(const std::vector<uint8_t>& code, const std::filesystem::path& output_asm) {
    std::ofstream out(output_asm);

    if (!out) {
        std::cerr << "Failed to create asm file\n";
        return;
    }

    uint16_t pc = 0x0000;
    size_t i = 0;

    while (i < code.size()) {
        uint8_t opcode = code[i];
        const Z80Instruction& inst = main_instruction_table[opcode];

        // Print address
        out << std::hex << std::setw(4) << std::setfill('0')
            << pc << ": ";

        // Print mnemonic
        out << inst.mnemonic;

        // Handle immediate operands
        if (inst.length == 2) {
            uint8_t imm = code[i + 1];
            out << " #" << std::setw(2) << (int)imm;
        }
        else if (inst.length == 3) {
            uint16_t imm =
                code[i + 1] |
                (code[i + 2] << 8);
            out << " #" << std::setw(4) << imm;
        }

        out << "\n";

        i += inst.length;
        pc += inst.length;
    }

    std::cout << "Disassembly written to " << output_asm << "\n";
}


