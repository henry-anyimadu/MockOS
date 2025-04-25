/**
* Studios 16-21: SimpleFileFactory.cpp
 **/
#include "mockos/SimpleFileFactory.h"
#include "mockos/TextFile.h"
#include "mockos/ImageFile.h"
#include <string>

AbstractFile* SimpleFileFactory::createFile(std::string filename) {
    // Get file extension
    const std::size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos) {
        return nullptr; // No extension found
    }

    std::string ext = filename.substr(pos + 1);

    AbstractFile* newFile = nullptr;

    if (ext == "img") {
        newFile = new ImageFile(filename);
    }
    else if (ext == "txt") {
        newFile = new TextFile(filename);
    }
    else {
        return nullptr; // Unknown extension
    }

    return newFile;
}