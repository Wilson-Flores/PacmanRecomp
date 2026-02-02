cmake_minimum_required(VERSION 3.20)

project(PacmanRecomp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set (SOURCES
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        src/core/Z80Disassembler.cpp
        src/io/RomManager.cpp
        src/utils/RomDumper.cpp
        src/core/Z80InstructionTable.cpp)

# Main executable
add_executable(PacmanRecomp ${SOURCES})

