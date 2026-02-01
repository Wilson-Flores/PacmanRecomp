#include "RomDumper.hpp"
#include <iomanip>
#include <fstream>
#include <iostream>


void dumpRomsForDebug(const std::unordered_map<std::string, std::vector<uint8_t>>& roms,
                      const std::string& output_folder) {

    std::filesystem::create_directories(output_folder);

    for (const auto& [name, data] : roms) {
        std::filesystem::path output_folder_path = std::filesystem::path(output_folder) / (name + ".txt");

        std::ofstream output_file(output_folder_path);

        if (!output_file) {
            std::cerr << "Failed to open file for dumping: " << name << "\n";
        }

        for (size_t i = 0; i < data.size(); ++i) {
            output_file << std::hex << std::setw(2) << std::setfill('0')
                    << static_cast<int>(data[i]) << " ";
            if ((i + 1) % 16 == 0)
                output_file << "\n";
        }

        std::cout << "Dumped " << name << " to " << output_folder_path << "\n";
    }
}


void clearRomDumpFolder(const std::string& folder) {
    if (std::filesystem::exists(folder)) {
        std::filesystem::remove_all(folder); // deletes folder + contents
        std::cout << "Deleted folder: " << folder << "\n";
    }
}


void concatenateRoms(const std::unordered_map<std::string, std::vector<uint8_t>>& roms,
                      const std::vector<std::string>& rom_order,
                      const std::string& output_folder) {

    std::ofstream output_file(output_folder, std::ios::binary);
    if (!output_file) {
        std::cerr << "Failed to open file for dumping: " << output_folder << "\n";
    }

    for (const std::string& rom_name : rom_order) {
        std::unordered_map<std::string, std::vector<uint8_t>>::const_iterator it = roms.find(rom_name);
        if (it == roms.end()) {
            std::cerr << "Failed to find rom: " << rom_name << "\n";
        }

        const std::vector<uint8_t>& data = it->second;

        output_file.write(reinterpret_cast<const char*>(data.data()), data.size());

        std::cout << "Added rom: " << rom_name << " (" << data.size() << " bytes)\n" ;

    }

    std::cout << "Combined ROM written to: " << output_folder << "\n";
}


void convertCombinedRomToText(
    const std::filesystem::path& input_rom_file,
    const std::filesystem::path& output_text_file
) {
    // Open the combined ROM file
    std::ifstream in(input_rom_file, std::ios::binary);
    if (!in) {
        std::cerr << "Failed to open ROM file: " << input_rom_file << "\n";
        return;
    }

    // Read entire file into memory
    std::vector<uint8_t> data(
        (std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>()
    );

    in.close();

    // Open output text file
    std::ofstream out(output_text_file);
    if (!out) {
        std::cerr << "Failed to create text file: " << output_text_file << "\n";
        return;
    }

    // Dump hex, 16 bytes per line
    for (size_t i = 0; i < data.size(); ++i) {
        out << std::hex
            << std::setw(2)
            << std::setfill('0')
            << static_cast<int>(data[i]) << " ";

        if ((i + 1) % 16 == 0)
            out << "\n";
    }

    std::cout << "Converted ROM to text: " << output_text_file << "\n";
}