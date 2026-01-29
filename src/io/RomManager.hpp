#ifndef ROM_MANAGER_HPP
#define ROM_MANAGER_HPP

#include <string>
#include <vector>
#include <unordered_map>

/* RomManager initializes with the folder path where the rom files are located.
 * We check that all the required rom files exist.
 * Load the roms into memory.
 */

class RomManager {
    public:
    RomManager(const std::string& folderPath);
    bool verifyRequiredRoms() const;
    std::unordered_map<std::string, std::vector<uint8_t>> loadRoms() const;

    private:
    std::string rom_folder;
    std::vector<std::string> required_files = {
        "pacman.6e",                           // Code ROM1
        "pacman.6f",                           // Code ROM2
        "pacman.6h",                           // Code ROM3
        "pacman.6j",                           // Code ROM4
        "82s123.7f",                           // Color ROM
        "82s126.4a",                           // Palette ROM
        "pacman.5e",                           // Tile ROM
        "pacman.5f",                           // Sprite ROM
        "82s126.1m",                           // Sound ROM 1
        "82s126.3m"                            // Sound ROM 2
    };
};


#endif
