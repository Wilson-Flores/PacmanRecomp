#ifndef ROMDUMPER_HPP
#define ROMDUMPER_HPP

#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>

// Function takes the unordered_map from RomManager and creates txt files for each rom file loaded in memory
void dumpRomsForDebug(const std::unordered_map<std::string, std::vector<uint8_t>>& roms,
                      const std::string& output_folder = "../rom_dumps");

// clears out the newly created folder
void clearRomDumpFolder(const std::string& folder = "../rom_dumps");

// creates a new rom file by combining certain rom files
void concatenateRoms(const std::unordered_map<std::string, std::vector<uint8_t>>& roms,
                     const std::vector<std::string>& rom_order,
                     const std::string& output_folder = "../rom_dumps");

// create a txt file for the combined rom file
void convertCombinedRomToText(const std::filesystem::path& input_rom_file,
                              const std::filesystem::path& output_text_file);


#endif