#include "RomManager.hpp"


RomManager::RomManager(const std::string& rom_folder_path) : rom_folder(rom_folder_path){}


bool RomManager::verifyRequiredRoms() const {
    for (const std::string& file : required_files) {
        std::filesystem::path full_path = std::filesystem::path(rom_folder) / file;

        if (!std::filesystem::exists(full_path)) {
            std::cerr << "Rom file not found: " << file << "\n";
            return false;
        }

        std::cout << "Rom file found: " << file << "\n";
    }
    return true;
}


std::unordered_map<std::string, std::vector<uint8_t>> RomManager::loadRoms() const {
    std::unordered_map<std::string, std::vector<uint8_t>> rom_data;

    for (const std::string& file : required_files) {
        std::filesystem::path full_path = std::filesystem::path(rom_folder) / file;

        std::ifstream rom_file(full_path, std::ios::binary);

        if (!rom_file) {
            std::cerr << "Rom file not found: " << file << "\n";
        }

        std::vector<uint8_t> data (
            (std::istreambuf_iterator<char>(rom_file)),
            std::istreambuf_iterator<char>()
            );

        rom_data[file] = data;

        std::cout << "Loaded ROM: " << file
                  << " (" << data.size() << " bytes)\n";
    }
    return rom_data;
}