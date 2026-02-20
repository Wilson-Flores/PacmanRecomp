#ifndef Z80_DISASSEMBLER_HPP
#define Z80_DISASSEMBLER_HPP

#include <vector>
#include <filesystem>


std::vector<uint8_t> loadRomFile(const std::string& rom_path);


void changeInstructionTable(const std::vector<uint8_t>& code);


void disassembleZ80(const std::vector<uint8_t>& code, const std::filesystem::path& output_asm);


#endif
