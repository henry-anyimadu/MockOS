/*
* CopyCommand.cpp implementation
* Implements the copy command, which allows the contents of a file to be copied into another
* Commands: displayInfo(), execute()
 */

#include "mockos/CopyCommand.h"
#include <iostream>
#include <sstream>

CopyCommand::CopyCommand(AbstractFileSystem* fs) : fileSystem(fs) {}

void CopyCommand::displayInfo() {
    std::cout << "Copy a file\n"
                 "Usage:\n"
                 "  cp <file_to_copy> <new_name_without_extension>\n";
}

int CopyCommand::execute(std::string args) {
    std::istringstream parser(args);
    std::string o_name, n_name;
    parser >> o_name >> n_name;

    //check for two tokens
    std::string extra;
    if (o_name.empty() || n_name.empty() || (parser>>extra))
        return cp_token_error;

    std::size_t dot = o_name.find_last_of('.');
    if (dot == std::string::npos) return cp_ext_error;

    std::string ext = o_name.substr(dot);
    std::string destName = n_name + ext;

    //check to see that the destination does not already exit
    // CopyCommand.cpp  (inside execute)
    AbstractFile* existing = fileSystem->openFile(destName);
    if (existing != nullptr) {
        fileSystem->closeFile(existing);           // close exactly what you opened
        std::cerr << "cp: \"" << destName << "\" already exists\n";
        return cp_repeat_file;                     // or command_failed
    }


    AbstractFile* o_ptr = fileSystem->openFile(o_name);
    if (o_ptr == nullptr) {
        std::cerr << "cp: cannot open \"" << o_name << "\"\n";
        return cp_pointer_error;
    }

    AbstractFile* clone_ptr = o_ptr->clone(destName);
    fileSystem->closeFile(o_ptr);

    if (clone_ptr == nullptr) {
        std::cerr << "cp: clone failed\n";
        return cp_clone_error;
    }

    int result = fileSystem->addFile(destName,clone_ptr);
    if (result!= success) {
        std::cerr << "cp: could not add \"" << destName << "\" to file system\n";
        delete clone_ptr;
        return result;
    }

    return success;


}