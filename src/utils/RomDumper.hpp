#ifndef ROMDUMPER_HPP
#define ROMDUMPER_HPP

#include <fstream>
#include <iomanip>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

void dumpRomsForDebug(const std::unordered_map<std::string, std::vector<uint8_t>>& roms,
                      const std::string& output_folder = "../rom_dumps");

void clearRomDumpFolder(const std::string& folder = "../rom_dumps");


#endif