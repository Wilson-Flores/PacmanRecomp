#include "RomDumper.hpp"


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