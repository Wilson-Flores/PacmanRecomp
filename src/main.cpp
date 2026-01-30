#include <filesystem>
#include <iostream>
#include "io/RomManager.hpp"
#include "utils/RomDumper.hpp"


int main() {
    RomManager rom_manager("../roms");

    if (!rom_manager.verifyRequiredRoms()) {
        std::cerr << "Please make sure all ROM files are in the 'roms/' folder.\n";
        return 1;
    }

    // Load roms into memory
    std::unordered_map<std::string, std::vector<uint8_t>> roms = rom_manager.loadRoms();
    // dump roms into txt files
    dumpRomsForDebug(roms);
    // clear rom_dumps folder
    // clearRomDumpFolder();

    return 0;
}