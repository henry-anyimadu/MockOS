/*
 *CPP File for the ls command
 */


#include "mockos/LSCommand.h"
#include <iostream>
#include <iomanip>

LSCommand::LSCommand(AbstractFileSystem* fs) : fileSystem(fs) {}


void LSCommand::displayInfo() {
    std::cout << "ls lists all files, invoke with: ls" << std::endl;
}

int LSCommand::execute(std::string args) {
    const std::size_t COL_WIDTH = 22; //for a max size of 20 char
    auto names = fileSystem->getFileNames();

    std::size_t col = 0;
    for (const auto& name : names) {
        std::cout << std::left << std::setw(COL_WIDTH) << name;
        if (++col % 2 == 0) std::cout << '\n'; // newline after every 2nd name
    }
    if (col % 2) std::cout << '\n';            // final newline if odd count
    return success;
}