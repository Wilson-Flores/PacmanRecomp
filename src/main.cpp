#include <filesystem>
#include <iostream>
#include "io/RomManager.hpp"
#include "utils/RomDumper.hpp"
#include "core/Z80Disassembler.hpp"


int main() {
    // RomManager rom_manager("../roms");
    //
    // if (!rom_manager.verifyRequiredRoms()) {
    //     std::cerr << "Please make sure all ROM files are in the 'roms/' folder.\n";
    //     return 1;
    // }
    //
    // // Load roms into memory
    // std::unordered_map<std::string, std::vector<uint8_t>> roms = rom_manager.loadRoms();
    //
    // // dump roms into txt files
    // dumpRomsForDebug(roms);
    //
    // // clear rom_dumps folder
    // // clearRomDumpFolder();
    //
    //
    // // Combine the core rom files
    // const std::vector<std::string> pacman_rom_order = {
    //     "pacman.6e",
    //     "pacman.6f",
    //     "pacman.6h",
    //     "pacman.6j"
    // };
    //
    // concatenateRoms(roms, pacman_rom_order, "../roms/pacman_program.rom");
    // convertCombinedRomToText(
    //     "../roms/pacman_program.rom",
    //     "../rom_dumps/pacman_program.txt"
    // );

    // convert combined rom file into asm file
    std::vector<uint8_t> pacman_rom = loadRomFile("../roms/pacman_program.rom");
    if (pacman_rom.empty())
        return 1;

    disassembleZ80(pacman_rom,"../roms/pacman.asm");

    return 0;
}