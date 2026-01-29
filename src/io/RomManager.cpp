#include "RomManager.hpp"
#include <filesystem>
#include <iostream>


RomManager::RomManager(const std::string& folderPath) : rom_folder(folderPath){}

bool RomManager::verifyRequiredRoms() const {
    for (const std::string& file : required_files) {
        std::filesystem::path fullPath = std::filesystem::path(rom_folder) / file;

        if (!std::filesystem::exists(fullPath)) {
            std::cerr << "Rom file not found: " << file << "\n";
            return false;
        }

        std::cout << "Rom file found: " << file << "\n";
    }
    return true;
}