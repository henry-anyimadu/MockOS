/**
 * Studios 16-21: SimpleFileSystem.cpp
 **/
#include "./mockos/SimpleFileSystem.h"
#include <string>

#include "mockos/ImageFile.h"
#include "mockos/TextFile.h"

using namespace std;

SimpleFileSystem::SimpleFileSystem() {
}

int SimpleFileSystem::addFile(std::string filename, AbstractFile *) {

}


int SimpleFileSystem::createFile(std::string filename) {
    //check to see if the file already exists
    for (string s : openFiles) {
        if (s == filename) {
            return duplicate_files;
        }
    }
    //decide what file to create based upon the file extension
    const std::size_t pos = filename.find_last_of('.');
    string ext = filename.substr(pos + 1);
    std::unique_ptr<AbstractFile> newFile;

    if (ext == "img") {
        //dynamically allocate an image file and add it to the files
        newFile = std::make_unique<ImageFile>(filename);
        if (addFile(std::move(filename), std::move(newFile).get())) {
            return success;
        }
        return allocation_error;
    }
    else if (ext == "txt") {
        //dynamically allocate an text file and add it to the files
        newFile = std::make_unique<TextFile>(filename);
        if (addFile(std::move(filename), std::move(newFile).get())) {
            return success;
        }
        return allocation_error;
    }
    else {
        return unknown_extension;
    }
}