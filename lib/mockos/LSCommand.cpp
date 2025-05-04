/*
 *CPP File for the ls command
 *Allows the user to view all files in the file system
 *Can use -m to view the file metadata
 */


#include "mockos/LSCommand.h"
#include "mockos/Constants.h"
#include <iostream>
#include <iomanip>
#include <algorithm>



LSCommand::LSCommand(AbstractFileSystem* fs) : fileSystem(fs) {}


void LSCommand::displayInfo() {
    std::cout << "ls lists all files\n"
                 "Usage:\n"
                 "  ls       (two‑column listing)\n"
                 "  ls -m    (one line per file with metadata)\n";
}


int LSCommand::execute(std::string args) {
    auto names = fileSystem->getFileNames();   // copy – we’ll scan twice

    // ---------- default two‑column view ----------
    if (args.empty()) {
        const std::size_t COL_W = 22;
        std::size_t col = 0;
        for (const auto& name : names) {
            std::cout << std::left << std::setw(COL_W) << name;
            if (++col % 2 == 0) std::cout << '\n';
        }
        if (col % 2) std::cout << '\n';
        return success;
    }

    // ---------- ‑m (meta) view ----------
    if (args == "-m") {
        /* 1) find longest file name and longest type string */
        std::size_t w_name = 0, w_type = 0;
        for (const auto& name : names) {
            w_name = std::max(w_name, name.size());
            std::string ext = name.substr(name.find_last_of('.') + 1);
            std::string type = (ext == "txt") ? "text" :
                               (ext == "img") ? "image" : ext;
            w_type = std::max(w_type, type.size());
        }
        w_name += BREATHING_ROOM;                 // a little breathing room
        w_type += BREATHING_ROOM;

        /* 2) print rows */
        for (const auto& name : names) {
            AbstractFile* fp = fileSystem->openFile(name);
            if (!fp) {
                std::cerr << "ls: cannot open \"" << name << "\"\n";
                return ls_m_file_error;
            }
            std::size_t size = fp->getSize();
            fileSystem->closeFile(fp);

            std::string ext  = name.substr(name.find_last_of('.') + 1);
            std::string type = (ext == "txt") ? "text" :
                               (ext == "img") ? "image" : ext;

            std::cout << std::left  << std::setw(w_name) << name
                      << std::left  << std::setw(w_type) << type
                      << std::right << size << '\n';
        }
        return success;
    }

    // unknown flag
    std::cerr << "ls: unrecognized option \"" << args << "\"\n";
    return ls_m_extension_error;
}

