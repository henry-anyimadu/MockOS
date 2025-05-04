/*
* DisplayCommand.cpp
* Implements the display command which allows the user to view contents of files
* Both raw and filtered implementations
 */

#include "mockos/DisplayCommand.h"
#include "mockos/BasicDisplayVisitor.h"   // visitor supplied by the framework
#include "mockos/ImageFile.h"   // add this include
#include <iostream>
#include <sstream>


DisplayCommand::DisplayCommand(AbstractFileSystem* fs) : fileSystem(fs) {}

void DisplayCommand::displayInfo() {
    std::cout << "Display the contents of a file\n"
                 "Usage:\n"
                 "  ds <filename>        (formatted)\n"
                 "  ds <filename> -d     (data only)\n";
}

int DisplayCommand::execute(std::string args) {
    std::istringstream parser(args);
    std::string filename, flag;
    parser >> filename;
    if (filename.empty()) return dp_file_error;

    bool dataOnly = false;
    if (parser >> flag) {
        if (flag == "-d") dataOnly = true;
        else return dp_ext_error; //unknown extension
    }
    if (parser >> flag) return dp_ext_error; //too many tokens

    //File Parsing
    AbstractFile* fp = fileSystem->openFile(filename);
    if (fp == nullptr) {
        std::cerr << "ds: cannot open \"" << filename << "\"\n";
        return dp_file_error;
    }

    int rc = success;

    if (dataOnly) {
        //unformatted dump
        for (char c: fp->read()) std::cout << c;
        std::cout <<'\n';
    } else {
        //formatted dump
        BasicDisplayVisitor visitor;
        fp->accept(&visitor);
    }

    if (fileSystem->closeFile(fp) != success) rc = dp_file_error;
    return rc;
}