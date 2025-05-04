/*
* DisplayCommand.cpp
 */

#include "mockos/DisplayCommand.h"
#include "mockos/BasicDisplayVisitor.h"   // visitor supplied by the framework
#include "mockos/ImageFile.h"   // add this include
#include <iostream>
#include <sstream>
#include <sys/stat.h>

#define MIN_IMG_SIZE 4

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
        //Adding in the dimension for proper formatting
        if (filename.size() >= MIN_IMG_SIZE && filename.compare(filename.size()-MIN_IMG_SIZE,MIN_IMG_SIZE, ".img")==0) {
            unsigned int n = fp->getSize();
            unsigned int dim = static_cast<unsigned int>(std::sqrt(n));
            std::cout << dim;
        }

        std::cout <<'\n';
    } else {
        //formatted dump
        BasicDisplayVisitor visitor;
        fp->accept(&visitor);
    }

    if (fileSystem->closeFile(fp) != success) rc = dp_file_error;
    return rc;
}