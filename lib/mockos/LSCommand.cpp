/*
 *CPP File for the ls command
 */


#include "mockos/LSCommand.h"
#include <iostream>
#include <iomanip>

LSCommand::LSCommand(AbstractFileSystem* fs) : fileSystem(fs) {}


void LSCommand::displayInfo() {
    std::cout << "ls lists all files\n"
                 "Usage:\n"
                 "  ls       (two‑column listing)\n"
                 "  ls -m    (one line per file with metadata)\n";
}

int LSCommand::execute(std::string args) {
    //safety checks for args
    const auto names = fileSystem->getFileNames();

    //DEFAULT TWO COLUMN VIEW
    if (args.empty()) {
        const std::size_t col_w = 22; //fits 20-char max nicely
        std::size_t col = 0;
        for (const auto& name: names) {
            std::cout << std::left << std::setw(col_w) << name;
            if (++col % 2 == 0) std::cout << '\n';
        }
        if (col % 2) std::cout << '\n';
        return success;
    }

    if (args == "-m") {
        for (const auto& name: names) {
            AbstractFile* fp = fileSystem->openFile(name);
            if (fp == nullptr) {
                std::cerr << "ls: cannot open \"" << name << "\"\n";
                return ls_m_file_error;
            }
            const std::size_t size = fp->getSize();
            fileSystem->closeFile(fp);

            std::string type = "unknown";
            const std::size_t dot = name.find_last_of('.');
            if (dot != std::string::npos) {
                const std::string ext = name.substr(dot+1);
                if (ext == "txt") type = "text";
                else if (ext == "img") type = "image";
                else type = ext;
            }

            //print out formatted
            std::cout << name << "   " << type << "        " << size << '\n';


        }
        return success;
    }

    std::cerr << "ls: unrecognized option \"" << args << "\"\n";
    return ls_m_extension_error;


}