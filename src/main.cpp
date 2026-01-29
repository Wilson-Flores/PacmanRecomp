#include <filesystem>
#include <iostream>
#include "io/RomManager.hpp"


int main() {
    RomManager rom_manager("../roms");

    if (!rom_manager.verifyRequiredRoms()) {
        std::cerr << "Please make sure all ROM files are in the 'roms/' folder.\n";
        return 1;
    }

    return 0;
}